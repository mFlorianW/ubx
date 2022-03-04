#define CATCH_CONFIG_MAIN
#include "ubx_frame_processor.hpp"
#include "ubx_message.hpp"
#include <catch2/catch.hpp>
#include <memory>

using namespace ubx;

class testing_handler;
using read_iterator = std::vector<std::uint8_t>::iterator;

class simple_uint8_message final : public message_base<simple_uint8_message>
{
public:
    template<typename read_iterator>
    simple_uint8_message(read_iterator &payload_begin, read_iterator &payload_end)
    {
        m_msg_value = *payload_begin;
    }

    std::uint32_t get_int_value() const noexcept
    {
        return m_msg_value;
    }

private:
    std::uint32_t m_msg_value;
};

class simple_msg_dispatcher final
{
public:
    template<typename msg_handler_t, typename read_iterator>
    bool create_and_dispatch_message(msg_handler_t &handler,
                                     std::uint8_t class_id,
                                     std::uint8_t message_id,
                                     read_iterator payload_begin,
                                     read_iterator payload_end)
    {
        auto msg = simple_uint8_message(payload_begin, payload_end);
        msg.dispatch(handler);
        return true;
    }
};

class factory_for_unsupported_messages final
{
public:
    template<typename msg_handler_t, typename read_iterator>
    bool create_and_dispatch_message(msg_handler_t &handler,
                                     std::uint8_t class_id,
                                     std::uint8_t message_id,
                                     read_iterator payload_begin,
                                     read_iterator payload_end)
    {
        return false;
    }
};

class testing_handler
{
public:
    void handle(simple_uint8_message &msg)
    {
        m_simple_uint8_handle_called = true;
        ++m_count_handle_called;
        REQUIRE(msg.get_int_value() == 0x20);
    }

    bool is_simple_uint8_handle_called() const noexcept
    {
        return m_simple_uint8_handle_called;
    }

    std::uint8_t how_often_is_handle_called() const noexcept
    {
        return m_count_handle_called;
    }

private:
    bool m_simple_uint8_handle_called{false};
    std::uint8_t m_count_handle_called{0};
};

namespace
{
auto frame_with_payload = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
auto frame_with_frame_begin_in_buffer =
    std::vector<std::uint8_t>{0x12, 0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
auto buffer_with_two_frames = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0, 0x22,
                                                        0x24, 0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
} // namespace

TEST_CASE("read in frame and dispatch message to the handler")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<simple_msg_dispatcher, testing_handler> frp{msg_factory, msg_handler};

    frp.process_data(frame_with_payload.begin(), frame_with_payload.end());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

TEST_CASE("read in frame frame but frame starts inside of the buffer and dispatch message to the handler")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<simple_msg_dispatcher, testing_handler> frp{msg_factory, msg_handler};

    frp.process_data(frame_with_frame_begin_in_buffer.cbegin(), frame_with_frame_begin_in_buffer.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

TEST_CASE("read in multiple frames in one buffer")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<simple_msg_dispatcher, testing_handler> frp{msg_factory, msg_handler};

    frp.process_data(buffer_with_two_frames.cbegin(), buffer_with_two_frames.cend());
    REQUIRE(msg_handler.how_often_is_handle_called() == 2);
}

TEST_CASE("handle unsupported message types and igonore them")
{
    factory_for_unsupported_messages msg_factory;
    testing_handler msg_handler;
    frame_processor<factory_for_unsupported_messages, testing_handler> frp{msg_factory, msg_handler};

    frp.process_data(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == false);
}

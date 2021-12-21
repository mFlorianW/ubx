#define CATCH_CONFIG_MAIN
#include "ubx_frame_processor.hpp"
#include "ubx_message.hpp"
#include <memory>
#include <catch2/catch.hpp>

using namespace ubx;

class testing_handler;
using read_iterator = std::vector<std::uint8_t>::iterator;
using msg = message<testing_handler>;

class simple_uint8_message final : public message_base<simple_uint8_message, testing_handler>
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


class simple_msg_factory final
{
public:
    template<typename  read_iterator>
    std::unique_ptr<msg> create_message(std::uint8_t class_id,
                                        std::uint8_t message_id,
                                        read_iterator payload_begin,
                                        read_iterator payload_end)
    {
        return std::make_unique<simple_uint8_message>(payload_begin, payload_end);
    }
};

class testing_handler
{
public:
    void handle(simple_uint8_message &msg)
    {
        m_simple_uint8_handle_called = true;
        REQUIRE(msg.get_int_value() == 0x20);
    }

    bool is_simple_uint8_handle_called() const noexcept
    {
        return m_simple_uint8_handle_called;
    }

private:
    bool m_simple_uint8_handle_called{false};
};

namespace
{
auto frame_with_payload =  std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
}

TEST_CASE("read in frame and dispatch message to the handler")
{
    simple_msg_factory msg_factory;
    testing_handler msg_handler;
    frame_processor<simple_msg_factory, testing_handler> frp{msg_factory, msg_handler};

    frp.process_data(frame_with_payload.begin(), frame_with_payload.end());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

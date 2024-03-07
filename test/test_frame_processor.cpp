// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "ubx_frame_processor.hpp"
#include "ubx_message.hpp"
#include <catch2/catch.hpp>
#include <memory>

using namespace ubx;

class testing_handler;
using read_iterator = std::vector<std::uint8_t>::iterator;
class simple_uint8_message final : public message
{
public:
    template<typename read_iterator>
    simple_uint8_message(read_iterator& payload_begin, read_iterator& payload_end)
        : message()
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
    bool create_and_dispatch_message(msg_handler_t& handler,
                                     std::uint8_t class_id,
                                     std::uint8_t message_id,
                                     read_iterator payload_begin,
                                     read_iterator payload_end)
    {
        auto msg = simple_uint8_message(payload_begin, payload_end);
        handler.handle(msg);
        return true;
    }
};

class factory_for_unsupported_messages final
{
public:
    template<typename msg_handler_t, typename read_iterator>
    bool create_and_dispatch_message(msg_handler_t& handler,
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
    void handle(simple_uint8_message& msg)
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
auto frame_fragemnt_1 = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01};
auto frame_fragemnt_2 = std::vector<std::uint8_t>{0x00, 0x20, 0x44, 0xB0};
} // namespace

TEST_CASE("read in frame and dispatch message to the handler")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, simple_msg_dispatcher> frp{msg_handler, msg_factory};

    frp.process_data(frame_with_payload.begin(), frame_with_payload.end());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

TEST_CASE("read in frame frame but frame starts inside of the buffer and dispatch message to the handler")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, simple_msg_dispatcher> frp{msg_handler, msg_factory};

    frp.process_data(frame_with_frame_begin_in_buffer.cbegin(), frame_with_frame_begin_in_buffer.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

TEST_CASE("read in multiple frames in one buffer")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, simple_msg_dispatcher> frp{msg_handler, msg_factory};

    frp.process_data(buffer_with_two_frames.cbegin(), buffer_with_two_frames.cend());
    REQUIRE(msg_handler.how_often_is_handle_called() == 2);
}

TEST_CASE("handle unsupported message types and igonore them")
{
    factory_for_unsupported_messages msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, factory_for_unsupported_messages> frp{msg_handler, msg_factory};

    frp.process_data(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == false);
}

TEST_CASE("create frame process without template parameter")
{
    message_handler msg_handler;
    ubx::message_dispatcher msg_dispatcher;
    frame_processor{msg_handler};
}

TEST_CASE("Handle frame fragments and put them together until the full frame is received.")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, simple_msg_dispatcher> frp{msg_handler, msg_factory};

    frp.process_data(frame_fragemnt_1.cbegin(), frame_fragemnt_1.cend());
    frp.process_data(frame_fragemnt_2.cbegin(), frame_fragemnt_2.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

TEST_CASE("Handle filled internel buffer. ")
{
    simple_msg_dispatcher msg_factory;
    testing_handler msg_handler;
    frame_processor<testing_handler, simple_msg_dispatcher> frp{msg_handler, msg_factory};

    std::array<std::uint8_t, 10> bsData{0, 21, 23, 34, 56, 6, 7, 8, 0, 10};
    // fill internal buffer with bullshit
    for (int i = 0; i < 30; i++) {
        frp.process_data(bsData.cbegin(), bsData.cend());
    }

    frp.process_data(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(msg_handler.is_simple_uint8_handle_called() == true);
}

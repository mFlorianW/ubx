// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "test_raw_messages.hpp"
#include "ubx_ack_ack_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("ack message is invalid on default construction")
{
    ack_ack_message msg;

    REQUIRE(msg.is_valid() == false);
}

TEST_CASE("ack message is valid after construction with valid data")
{
    ack_ack_message msg(valid_ack_msg.cbegin(), valid_ack_msg.cend());

    REQUIRE(msg.is_valid() == true);
}

TEST_CASE("ack message shall give the class id for the acknowledged message")
{
    ack_ack_message msg(valid_ack_msg.cbegin(), valid_ack_msg.cend());
    constexpr std::uint8_t expected_class_id = 0x20;

    REQUIRE(msg.get_acknowledged_class_id() == expected_class_id);
}

TEST_CASE("ack message shall give the messagie id for the acknowledged message")
{
    ack_ack_message msg(valid_ack_msg.cbegin(), valid_ack_msg.cend());
    constexpr std::uint8_t expected_message_id = 0x10;

    REQUIRE(msg.get_acknowledged_message_id() == expected_message_id);
}

TEST_CASE("ack message shall be invalid when the raw data is not long enough")
{
    ack_ack_message msg(invalid_ack_msg.cbegin(), invalid_ack_msg.cend());

    REQUIRE(msg.is_valid() == false);
}

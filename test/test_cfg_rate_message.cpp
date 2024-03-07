// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "ubx_cfg_rate_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

namespace
{
auto valid_cfg_rate_msg = std::vector<std::uint8_t>{0x65, 0x00, 0x23, 0x00, 0x01, 0x00};
auto invalid_cfg_rate_msg = std::vector<std::uint8_t>{0x65, 0x00, 0x23, 0x00, 0x01};
} // namespace

TEST_CASE("Default initialized UBX-CFG-RATE message shall be invalid.")
{
    cfg_rate_message msg;
    REQUIRE(msg.is_valid() == false);
}

TEST_CASE("The UBX-CFG-RATE message shall give the 'measRate' from valid raw data.")
{
    cfg_rate_message msg{valid_cfg_rate_msg.cbegin(), valid_cfg_rate_msg.cend()};
    constexpr std::uint16_t expectedMeasValue = 0x65;
    REQUIRE(msg.get_meas_rate() == expectedMeasValue);
}

TEST_CASE("The UBX-CFG-RATE message shall give the 'navRate' from valid raw data.")
{
    cfg_rate_message msg{valid_cfg_rate_msg.cbegin(), valid_cfg_rate_msg.cend()};
    constexpr std::uint16_t expectedMeasValue = 0x23;
    REQUIRE(msg.get_nav_rate() == expectedMeasValue);
}

TEST_CASE("The UBX-CFG-RATE message shall give the 'timeRef' from valid raw data.")
{
    cfg_rate_message msg{valid_cfg_rate_msg.cbegin(), valid_cfg_rate_msg.cend()};
    REQUIRE(msg.get_time_ref() == time_ref::gps);
}

TEST_CASE("The UBX-CFG-RATE message shall be valid when payload is successful parsed.")
{
    cfg_rate_message msg{valid_cfg_rate_msg.cbegin(), valid_cfg_rate_msg.cend()};
    REQUIRE(msg.is_valid() == true);
}

TEST_CASE("The UBX-CFG-RATE message shall be invalid when the payload is to short.")
{
    cfg_rate_message msg{invalid_cfg_rate_msg.cbegin(), invalid_cfg_rate_msg.cend()};
    REQUIRE(msg.is_valid() == false);
}

TEST_CASE("The UBX-CFG-RATE message shall be able to serialize 'measRate'")
{
    std::array<std::uint8_t, cfg_rate_message::message_length> outBuffer;
    cfg_rate_message msg;
    msg.set_meas_rate(0x65);

    msg.serialize(outBuffer.begin(), outBuffer.end());

    REQUIRE(outBuffer[0] == valid_cfg_rate_msg[0]);
    REQUIRE(outBuffer[1] == valid_cfg_rate_msg[1]);
}

TEST_CASE("The UBX-CFG-RATE message shall be able to serialize 'navRate'")
{
    std::array<std::uint8_t, cfg_rate_message::message_length> outBuffer;
    cfg_rate_message msg;
    msg.set_nav_rate(0x23);

    msg.serialize(outBuffer.begin(), outBuffer.end());

    REQUIRE(outBuffer[2] == valid_cfg_rate_msg[2]);
    REQUIRE(outBuffer[3] == valid_cfg_rate_msg[3]);
}

TEST_CASE("The UBX-CFG-RATE message shall be able to serialize 'timeRef'")
{
    std::array<std::uint8_t, cfg_rate_message::message_length> outBuffer;
    cfg_rate_message msg;
    msg.set_time_ref(time_ref::gps);

    msg.serialize(outBuffer.begin(), outBuffer.end());

    REQUIRE(outBuffer[4] == valid_cfg_rate_msg[4]);
    REQUIRE(outBuffer[5] == valid_cfg_rate_msg[5]);
}

TEST_CASE("The UBX-CFG-RATE message shall return false when buffer is too small.'")
{
    std::array<std::uint8_t, cfg_rate_message::message_length - 1> outBuffer;
    cfg_rate_message msg;
    msg.set_time_ref(time_ref::gps);

    REQUIRE(msg.serialize(outBuffer.begin(), outBuffer.end()) == false);
}

TEST_CASE("The UBX-CFG-RATE message shall return true when successful deserialized.'")
{
    std::array<std::uint8_t, cfg_rate_message::message_length> outBuffer;
    cfg_rate_message msg;
    msg.set_time_ref(time_ref::gps);

    REQUIRE(msg.serialize(outBuffer.begin(), outBuffer.end()) == true);
}

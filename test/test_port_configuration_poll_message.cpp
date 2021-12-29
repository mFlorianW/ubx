#define CATCH_CONFIG_MAIN
#include "ubx_port_configuration_poll_message.hpp"
#include <catch2/catch.hpp>
#include <array>

using namespace ubx;

namespace
{
constexpr auto valid_uart0_port_configuration_poll = std::array<std::uint8_t, 1>{ 0x00 };
constexpr auto valid_uart1_port_configuration_poll = std::array<std::uint8_t, 1>{ 0x01 };
}

TEST_CASE("port configuration shall be serializable with uart0")
{
    auto port_cfg_poll = port_configuration_poll_message();
    auto result = std::array<std::uint8_t, 1>{};

    port_cfg_poll.serialize(result.begin(), result.end());

    REQUIRE(result == valid_uart0_port_configuration_poll);
}

TEST_CASE("port configuration shall be serializable with uart1")
{
    auto port_cfg_poll = port_configuration_poll_message(port_id::uart1);
    auto result = std::array<std::uint8_t, 1>{};

    port_cfg_poll.serialize(result.begin(), result.end());

    REQUIRE(result == valid_uart1_port_configuration_poll);
}

TEST_CASE("port serialize shall return false when buffer is to small")
{
    auto port_cfg_poll = port_configuration_poll_message(port_id::uart0);
    auto broken_payload_buffer = std::array<std::uint8_t, 0>{};

    bool result = port_cfg_poll.serialize(broken_payload_buffer.begin(), broken_payload_buffer.end());

    REQUIRE(result == false);
}

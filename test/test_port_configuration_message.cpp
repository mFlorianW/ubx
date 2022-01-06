#define CATCH_CONFIG_MAIN
#include "ubx_port_configuration_message.hpp"
#include "test_raw_messages.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("Default constructed port configuration shall be invalid")
{
    auto uart_port_cfg = port_configuration_message();

    REQUIRE(uart_port_cfg.is_valid() == false);
}

TEST_CASE("port configuration shall return port from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};

    REQUIRE(uart_port_cfg.get_port_id() == port_id::uart0);
}

TEST_CASE("uart port configuration shall return tx ready configuration from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_tx_ready_cfg = tx_ready_configuration
    {
        .enabled = true,
        .polarity = 1,
        .pin = 10,
        .threshold = 0x04
    };

    auto tx_ready_cfg = uart_port_cfg.get_tx_ready_configuration();

    REQUIRE(tx_ready_cfg == expected_tx_ready_cfg);
}

TEST_CASE("port configuration shall return uart configuration from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_uart_cfg = uart_configuration
    {
        .data_length = static_cast<std::uint32_t>(data_length::bit7),
        .parity = static_cast<std::uint32_t>(parity::no_parity),
        .stop_bits = static_cast<std::uint32_t>(stop_bits::one_stop_bit)
    };

    auto uart_cfg = uart_port_cfg.get_uart_configuration();

    REQUIRE(uart_cfg == expected_uart_cfg);
}

TEST_CASE("port configuration shall return baud_rate configuration from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_baud_rate = static_cast<std::uint32_t>(115200);
    auto baud_rate = uart_port_cfg.get_baud_rate();

    REQUIRE(baud_rate == expected_baud_rate);
}

TEST_CASE("port configuration shall return protocol_in_mask configuration from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_protocol_mask_in = protocol_in_mask
    {
        .ubx_in = true,
        .nema_in = true,
        .rtcm_in = false,
        .rtcm3_in = false,
    };

    auto protocol_mask_in = uart_port_cfg.get_protocol_in_mask();

    REQUIRE(protocol_mask_in == expected_protocol_mask_in);
}

TEST_CASE("port configuration shall return protocol_out_mask configuration from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_protocol_mask_out = protocol_out_mask
    {
        .ubx_out = true,
        .nmea_out = true,
        .rtcm3_out = false,
    };

    auto protocol_out_mask = uart_port_cfg.get_protocol_out_mask();

    REQUIRE(protocol_out_mask == expected_protocol_mask_out);
}

TEST_CASE("port configuration shall return port_flags from valid data")
{
    auto uart_port_cfg = port_configuration_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_port_flags = port_flags
    {
        .extended_tx_timeout = true,
    };

    auto port_flags = uart_port_cfg.get_port_flags();

    REQUIRE(port_flags == expected_port_flags);
}

TEST_CASE("port configuration shall be invalid when payload is corrupted")
{
    auto uart_port_cfg = port_configuration_message{invalid_uart_port_config.begin(), invalid_uart_port_config.end()};

    REQUIRE(uart_port_cfg.is_valid() == false);
}

TEST_CASE("port configuration shall serialize the set port id.")
{
    auto message_buffer = std::array<std::uint8_t, port_configuration_message_length>{0};
    auto port_cfg = port_configuration_message{};

    port_cfg.set_port_id(port_id::uart1);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[0] == valid_uart_port_config[0]);
}

#define CATCH_CONFIG_MAIN
#include "test_raw_messages.hpp"
#include "ubx_cfg_prt_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

namespace
{
constexpr auto valid_uart0_port_configuration_poll = std::array<std::uint8_t, 1>{0x01};
constexpr auto valid_uart1_port_configuration_poll = std::array<std::uint8_t, 1>{0x02};
} // namespace

TEST_CASE("Default constructed port configuration shall be invalid")
{
    auto uart_port_cfg = cfg_prt_message();

    REQUIRE(uart_port_cfg.is_valid() == false);
}

TEST_CASE("port configuration shall return port from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};

    REQUIRE(uart_port_cfg.get_port_id() == port_id::uart0);
}

TEST_CASE("uart port configuration shall return tx ready configuration from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_tx_ready_cfg = tx_ready_configuration{.enabled = true, .polarity = 1, .pin = 10, .threshold = 0x04};

    auto tx_ready_cfg = uart_port_cfg.get_tx_ready_configuration();

    REQUIRE(tx_ready_cfg == expected_tx_ready_cfg);
}

TEST_CASE("port configuration shall return uart configuration from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_uart_cfg = uart_configuration{.data_length = static_cast<std::uint32_t>(data_length::bit7),
                                                .parity = static_cast<std::uint32_t>(parity::no_parity),
                                                .stop_bits = static_cast<std::uint32_t>(stop_bits::one_stop_bit)};

    auto uart_cfg = uart_port_cfg.get_uart_configuration();

    REQUIRE(uart_cfg == expected_uart_cfg);
}

TEST_CASE("port configuration shall return baud_rate configuration from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_baud_rate = static_cast<std::uint32_t>(115200);
    auto baud_rate = uart_port_cfg.get_baud_rate();

    REQUIRE(baud_rate == expected_baud_rate);
}

TEST_CASE("port configuration shall return protocol_in_mask configuration from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_protocol_mask_in = protocol_in_mask{
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
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_protocol_mask_out = protocol_out_mask{
        .ubx_out = true,
        .nmea_out = true,
        .rtcm3_out = false,
    };

    auto protocol_out_mask = uart_port_cfg.get_protocol_out_mask();

    REQUIRE(protocol_out_mask == expected_protocol_mask_out);
}

TEST_CASE("port configuration shall return port_flags from valid data")
{
    auto uart_port_cfg = cfg_prt_message{valid_uart_port_config.begin(), valid_uart_port_config.end()};
    auto expected_port_flags = port_flags{
        .extended_tx_timeout = true,
    };

    auto port_flags = uart_port_cfg.get_port_flags();

    REQUIRE(port_flags == expected_port_flags);
}

TEST_CASE("port configuration shall be invalid when payload is corrupted")
{
    auto uart_port_cfg = cfg_prt_message{invalid_uart_port_config.begin(), invalid_uart_port_config.end()};

    REQUIRE(uart_port_cfg.is_valid() == false);
}

TEST_CASE("port configuration shall serialize the set port id.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};

    port_cfg.set_port_id(port_id::uart0);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[0] == valid_uart_port_config[0]);
}

TEST_CASE("port configuration shall serialize the set tx ready configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    auto tx_ready_cfg = tx_ready_configuration{.enabled = true, .polarity = 1, .pin = 10, .threshold = 0x04};

    port_cfg.set_tx_ready_configuration(tx_ready_cfg);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[2] == valid_uart_port_config[2]);
    REQUIRE(message_buffer[3] == valid_uart_port_config[3]);
}

TEST_CASE("port configuration shall serialize the set uart configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    constexpr auto uart_cfg = uart_configuration{.data_length = static_cast<std::uint32_t>(data_length::bit7),
                                                 .parity = static_cast<std::uint32_t>(parity::no_parity),
                                                 .stop_bits = static_cast<std::uint32_t>(stop_bits::one_stop_bit)};

    port_cfg.set_uart_configuration(uart_cfg);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[4] == valid_uart_port_config[4]);
    REQUIRE(message_buffer[5] == valid_uart_port_config[5]);
    REQUIRE(message_buffer[6] == valid_uart_port_config[6]);
    REQUIRE(message_buffer[7] == valid_uart_port_config[7]);
}

TEST_CASE("port configuration shall serialize the set baud rate configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    auto baud_rate = static_cast<std::uint32_t>(115200);

    port_cfg.set_baud_rate(baud_rate);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[8] == valid_uart_port_config[8]);
    REQUIRE(message_buffer[9] == valid_uart_port_config[9]);
    REQUIRE(message_buffer[10] == valid_uart_port_config[10]);
    REQUIRE(message_buffer[11] == valid_uart_port_config[11]);
}

TEST_CASE("port configuration shall serialize the set protocol in mask configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    auto proto_in_mask = protocol_in_mask{
        .ubx_in = true,
        .nema_in = true,
        .rtcm_in = false,
        .rtcm3_in = false,
    };

    port_cfg.set_protocol_in_mask(proto_in_mask);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[12] == valid_uart_port_config[12]);
    REQUIRE(message_buffer[13] == valid_uart_port_config[13]);
}

TEST_CASE("port configuration shall serialize the set protocol out mask configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    auto proto_out_mask = protocol_out_mask{
        .ubx_out = true,
        .nmea_out = true,
        .rtcm3_out = false,
    };

    port_cfg.set_protocol_out_mask(proto_out_mask);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[14] == valid_uart_port_config[14]);
    REQUIRE(message_buffer[15] == valid_uart_port_config[15]);
}

TEST_CASE("port configuration shall serialize the set port flags configuration.")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};
    auto prt_flags = port_flags{
        .extended_tx_timeout = true,
    };

    port_cfg.set_port_flags(prt_flags);
    port_cfg.serialize(message_buffer.begin(), message_buffer.end());

    REQUIRE(message_buffer[16] == valid_uart_port_config[16]);
    REQUIRE(message_buffer[17] == valid_uart_port_config[17]);
}

TEST_CASE("port configuration shall return when serialization is successful")
{
    auto message_buffer = std::array<std::uint8_t, cfg_prt_message::cfg_port_message_length>{0};
    auto port_cfg = cfg_prt_message{};

    REQUIRE(port_cfg.serialize(message_buffer.begin(), message_buffer.end()) == true);
}

TEST_CASE("port configuration poll shall be serializable with uart0")
{
    auto port_cfg = cfg_prt_message{};
    auto result = std::array<std::uint8_t, 1>{};

    port_cfg.set_port_id(port_id::uart0);
    port_cfg.serialize_poll_message(result.begin(), result.end());

    REQUIRE(result == valid_uart0_port_configuration_poll);
}

TEST_CASE("port configuration poll shall be serializable with uart1")
{
    auto port_cfg = cfg_prt_message{};
    auto result = std::array<std::uint8_t, 1>{};

    port_cfg.set_port_id(port_id::uart1);
    port_cfg.serialize_poll_message(result.begin(), result.end());

    REQUIRE(result == valid_uart1_port_configuration_poll);
}

TEST_CASE("port serialize poll shall return false when buffer is to small")
{
    auto port_cfg = cfg_prt_message{};
    auto broken_payload_buffer = std::array<std::uint8_t, 0>{};

    bool result = port_cfg.serialize_poll_message(broken_payload_buffer.begin(), broken_payload_buffer.end());

    REQUIRE(result == false);
}

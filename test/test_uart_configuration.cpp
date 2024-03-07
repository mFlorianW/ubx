// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "ubx_uart_configuration.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("uart_configuration get data_length as enum bit5")
{
    constexpr auto expected_data_length = data_length::bit5;
    auto uart_cfg = uart_configuration{
        .data_length = 0x00,
    };

    REQUIRE(uart_cfg.get_data_length() == expected_data_length);
}

TEST_CASE("uart_configuration get data_length as enum bit6")
{
    constexpr auto expected_data_length = data_length::bit6;
    auto uart_cfg = uart_configuration{
        .data_length = 0x01,
    };

    REQUIRE(uart_cfg.get_data_length() == expected_data_length);
}

TEST_CASE("uart_configuration get data_length as enum bit7")
{
    constexpr auto expected_data_length = data_length::bit7;
    auto uart_cfg = uart_configuration{
        .data_length = 0x02,
    };

    REQUIRE(uart_cfg.get_data_length() == expected_data_length);
}

TEST_CASE("uart_configuration get data_length as enum bit8")
{
    constexpr auto expected_data_length = data_length::bit8;
    auto uart_cfg = uart_configuration{
        .data_length = 0x03,
    };

    REQUIRE(uart_cfg.get_data_length() == expected_data_length);
}

TEST_CASE("uart_configuration get partity as enum even_paritiy")
{
    constexpr auto expected_paritiy = parity::even_parity;
    auto uart_cfg = uart_configuration{
        .parity = 0x00,
    };

    REQUIRE(uart_cfg.get_paritiy() == expected_paritiy);
}

TEST_CASE("uart_configuration get partity as enum odd_paritiy")
{
    constexpr auto expected_paritiy = parity::odd_parity;
    auto uart_cfg = uart_configuration{
        .parity = 0x01,
    };

    REQUIRE(uart_cfg.get_paritiy() == expected_paritiy);
}

TEST_CASE("uart_configuration get partity as enum no_paritiy")
{
    constexpr auto expected_paritiy = parity::no_parity;
    auto uart_cfg = uart_configuration{
        .parity = 0x04,
    };

    REQUIRE(uart_cfg.get_paritiy() == expected_paritiy);
}

TEST_CASE("uart_configuration get stop bits as enum one_stop_bit")
{
    constexpr auto expected_stop_bits = stop_bits::one_stop_bit;
    auto uart_cfg = uart_configuration{
        .stop_bits = 0x00,
    };

    REQUIRE(uart_cfg.get_stop_bits() == expected_stop_bits);
}

TEST_CASE("uart_configuration get stop bits as enum one_and_half_stop_bit")
{
    constexpr auto expected_stop_bits = stop_bits::one_and_half_stop_bit;
    auto uart_cfg = uart_configuration{
        .stop_bits = 0x01,
    };

    REQUIRE(uart_cfg.get_stop_bits() == expected_stop_bits);
}

TEST_CASE("uart_configuration get stop bits as enum two_stop_bits")
{
    constexpr auto expected_stop_bits = stop_bits::two_stop_bits;
    auto uart_cfg = uart_configuration{
        .stop_bits = 0x02,
    };

    REQUIRE(uart_cfg.get_stop_bits() == expected_stop_bits);
}

TEST_CASE("uart_configuration get stop bits as enum half_stop_bit")
{
    constexpr auto expected_stop_bits = stop_bits::half_stop_bit;
    auto uart_cfg = uart_configuration{
        .stop_bits = 0x03,
    };

    REQUIRE(uart_cfg.get_stop_bits() == expected_stop_bits);
}

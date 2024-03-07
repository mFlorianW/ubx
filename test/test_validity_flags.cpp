// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "ubx_validity_flags.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("validity flags shall return true when valid date flag is set otherwise false")
{
    auto val_flags = validity_flags{
        .valid_date = true,
    };

    REQUIRE(val_flags.is_date_valid() == true);
    val_flags.valid_date = false;
    REQUIRE(val_flags.is_date_valid() == false);
}

TEST_CASE("validity flags shall return true when valid time flag is set otherwise false")
{
    auto val_flags = validity_flags{
        .valid_time = true,
    };

    REQUIRE(val_flags.is_time_valid() == true);
    val_flags.valid_time = false;
    REQUIRE(val_flags.is_time_valid() == false);
}

TEST_CASE("validity flags shall return true when fully resolved flag is set otherwise false")
{
    auto val_flags = validity_flags{
        .fully_resolved = true,
    };

    REQUIRE(val_flags.is_fully_resolved() == true);
    val_flags.fully_resolved = false;
    REQUIRE(val_flags.is_fully_resolved() == false);
}

TEST_CASE("validity flags shall return true when valid message flag is set otherwise false")
{
    auto val_flags = validity_flags{
        .valid_msg = true,
    };

    REQUIRE(val_flags.is_msg_valid() == true);
    val_flags.valid_msg = false;
    REQUIRE(val_flags.is_msg_valid() == false);
}

TEST_CASE("validity flags shall be able to be compare")
{
    auto val_flags = validity_flags{
        .valid_date = true,
        .valid_time = false,
        .fully_resolved = false,
        .valid_msg = true,
    };

    auto val_flags2 = validity_flags{
        .valid_date = true,
        .valid_time = false,
        .fully_resolved = false,
        .valid_msg = true,
    };

    REQUIRE(val_flags == val_flags2);
}

TEST_CASE("validity flags shall be able to check for unequal.")
{
    auto val_flags = validity_flags{
        .valid_date = true,
        .valid_time = false,
        .fully_resolved = false,
        .valid_msg = true,
    };

    auto val_flags2 = validity_flags{
        .valid_date = true,
        .valid_time = false,
        .fully_resolved = true,
        .valid_msg = true,
    };

    REQUIRE(val_flags != val_flags2);
}

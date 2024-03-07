// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#define CATCH_CONFIG_MAIN
#include "ubx_protocol_out_mask.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("protocol_mask_out shall give ubx_out to true when set")
{
    auto proto_mask_out = protocol_out_mask{
        .ubx_out = 0x01,
    };

    REQUIRE(proto_mask_out.is_ubx_out_enabled() == true);
}

TEST_CASE("protocol_mask_out shall give nmea_out to true when set")
{
    auto proto_mask_out = protocol_out_mask{
        .nmea_out = 0x01,
    };

    REQUIRE(proto_mask_out.is_nmea_out_enabled() == true);
}

TEST_CASE("protocol_mask_out shall give rtcm3 to true when set")
{
    auto proto_mask_out = protocol_out_mask{
        .rtcm3_out = 0x01,
    };

    REQUIRE(proto_mask_out.is_rtcm3_out_enabled() == true);
}

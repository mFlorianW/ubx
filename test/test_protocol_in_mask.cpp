#define CATCH_CONFIG_MAIN
#include "ubx_protocol_in_mask.hpp"
#include <catch2/catch.hpp>

using namespace ubx;
TEST_CASE("protocol_mask_in shall return true when ubx_in is set")
{
    auto proto_mask_in = protocol_in_mask{
        .ubx_in = 0x01,
    };

    REQUIRE(proto_mask_in.is_ubx_in_enabled() == true);
}

TEST_CASE("protocol_mask_in shall return true when nema_in is set")
{
    auto proto_mask_in = protocol_in_mask{
        .nema_in = 0x01,
    };

    REQUIRE(proto_mask_in.is_nema_in_enabled() == true);
}

TEST_CASE("protocol_mask_in shall return true when rtcm_in is set")
{
    auto proto_mask_in = protocol_in_mask{
        .rtcm_in = 0x01,
    };

    REQUIRE(proto_mask_in.is_rtcm_in_enabled() == true);
}

TEST_CASE("protocol_mask_in shall return true when rtcm3_in is set")
{
    auto proto_mask_in = protocol_in_mask{
        .rtcm3_in = 0x01,
    };

    REQUIRE(proto_mask_in.is_rtcm3_in_enabled() == true);
}

#define CATCH_CONFIG_MAIN
#include "ubx_port_flags.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("port_flags shall return true when extended_tx_timeout is set")
{
    auto flags = port_flags
    {
        .extended_tx_timeout = 0x01,
    };

    REQUIRE(flags.is_extended_tx_timeout_enabled() == true);
}

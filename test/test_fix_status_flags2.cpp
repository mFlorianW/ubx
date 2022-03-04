#define CATCH_CONFIG_MAIN
#include "ubx_fix_status_flags2.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("fix status flags2 shall return true when confirmed available flag is set otherwise false")
{
    auto status_flags = fix_status_flags2{
        .confirmed_available = true,
    };

    REQUIRE(status_flags.is_confirmed_available() == true);
    status_flags.confirmed_available = false;
    REQUIRE(status_flags.is_confirmed_available() == false);
}

TEST_CASE("fix status flags2 shall return true when confirmed date flag is set otherwise false")
{
    auto status_flags = fix_status_flags2{
        .confirmed_date = true,
    };

    REQUIRE(status_flags.is_date_confirmed() == true);
    status_flags.confirmed_date = false;
    REQUIRE(status_flags.is_date_confirmed() == false);
}

TEST_CASE("fix status flags2 shall return true when confirmed time flag is set otherwise false")
{
    auto status_flags = fix_status_flags2{
        .confirmed_time = true,
    };

    REQUIRE(status_flags.is_time_confirmed() == true);
    status_flags.confirmed_time = false;
    REQUIRE(status_flags.is_time_confirmed() == false);
}

TEST_CASE("fix status flags2 shall be able to be compare")
{
    auto fix_st_flags = fix_status_flags2{.confirmed_available = true, .confirmed_date = false, .confirmed_time = true};

    auto fix_st_flags2 =
        fix_status_flags2{.confirmed_available = true, .confirmed_date = false, .confirmed_time = true};

    REQUIRE(fix_st_flags == fix_st_flags2);
}

TEST_CASE("fix status flags2 shall be able to be check for unequal")
{
    auto fix_st_flags = fix_status_flags2{.confirmed_available = true, .confirmed_date = true, .confirmed_time = true};

    auto fix_st_flags2 =
        fix_status_flags2{.confirmed_available = true, .confirmed_date = false, .confirmed_time = true};

    REQUIRE(fix_st_flags != fix_st_flags2);
}

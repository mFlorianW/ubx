#define CATCH_CONFIG_MAIN
#include "ubx_fix_status_flags3.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("fix status flags3 shall return true when invalid Llh flag is set otherwise false")
{
    auto status_flags = fix_status_flags3
    {
        .invalid_llh = true,
    };

    REQUIRE(status_flags.is_llh_invalid() == true);
    status_flags.invalid_llh = false;
    REQUIRE(status_flags.is_llh_invalid() == false);
}

TEST_CASE("fix status flags3 shall return last correction values")
{
    auto status_flags = fix_status_flags3{};

    status_flags.last_correction_age = not_available;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::not_available);
    status_flags.last_correction_age = age_between_0_to_1s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_0_to_1s);
    status_flags.last_correction_age = age_between_1_to_2s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_1_to_2s);
    status_flags.last_correction_age = age_between_2_to_5s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_2_to_5s);
    status_flags.last_correction_age = age_between_5_to_10s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_5_to_10s);
    status_flags.last_correction_age = age_between_10_to_15s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_10_to_15s);
    status_flags.last_correction_age = age_between_15_to_20s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_15_to_20s);
    status_flags.last_correction_age = age_between_20_to_30s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_20_to_30s);
    status_flags.last_correction_age = age_between_30_to_45s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_30_to_45s);
    status_flags.last_correction_age = age_between_45_to_60s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_45_to_60s);
    status_flags.last_correction_age = age_between_60_to_90s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_60_to_90s);
    status_flags.last_correction_age = age_between_60_to_90s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_between_60_to_90s);
    status_flags.last_correction_age = age_greater_than_120s;
    REQUIRE(status_flags.get_last_correction_age() == last_correction_age::age_greater_than_120s);
}

TEST_CASE("fix status flags3 shall be able to be compare")
{
    auto fix_st_flags = fix_status_flags3
    {
        .invalid_llh = true,
        .last_correction_age = last_correction_age::age_between_15_to_20s,
    };

    auto fix_st_flags2 = fix_status_flags3
    {
        .invalid_llh = true,
        .last_correction_age = last_correction_age::age_between_15_to_20s,
    };

    REQUIRE(fix_st_flags == fix_st_flags2);
}

TEST_CASE("fix status flags3 shall be able to be check for unequal")
{
    auto fix_st_flags = fix_status_flags3
    {
        .invalid_llh = true,
        .last_correction_age = last_correction_age::age_between_15_to_20s,
    };

    auto fix_st_flags2 = fix_status_flags3
    {
        .invalid_llh = true,
        .last_correction_age = last_correction_age::age_between_0_to_1s,
    };

    REQUIRE(fix_st_flags != fix_st_flags2);
}

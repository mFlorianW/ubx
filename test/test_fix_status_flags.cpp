#define CATCH_CONFIG_MAIN
#include "ubx_fix_status_flags.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("fix status flags shall return true when gnss fix flag is set otherwise false")
{
    auto fix_st_flags = fix_status_flags
    {
        .gnss_fix_ok = true,
    };

    REQUIRE(fix_st_flags.is_gnss_fix_ok() == true);
    fix_st_flags.gnss_fix_ok = false;
    REQUIRE(fix_st_flags.is_gnss_fix_ok() == false);
}

TEST_CASE("fix status flags shall return true when differential corrections flag is set otherwise false")
{
    auto fix_st_flags = fix_status_flags
    {
        .diff_soln = true,
    };

    REQUIRE(fix_st_flags.is_diff_soln_applied() == true);
    fix_st_flags.diff_soln = false;
    REQUIRE(fix_st_flags.is_diff_soln_applied() == false);
}

TEST_CASE("fix status flags shall return different psm states")
{
    auto fix_st_flags = fix_status_flags{};

    fix_st_flags.psm_state = static_cast<std::uint8_t>(psm_state::not_active);
    REQUIRE(fix_st_flags.get_psm_state() == psm_state::not_active);
    fix_st_flags.psm_state = static_cast<std::uint8_t>(psm_state::enabled);
    REQUIRE(fix_st_flags.get_psm_state() == psm_state::enabled);
    fix_st_flags.psm_state = static_cast<std::uint8_t>(psm_state::inactive);
    REQUIRE(fix_st_flags.get_psm_state() == psm_state::inactive);
    fix_st_flags.psm_state = static_cast<std::uint8_t>(psm_state::acquisition);
    REQUIRE(fix_st_flags.get_psm_state() == psm_state::acquisition);
    fix_st_flags.psm_state = static_cast<std::uint8_t>(psm_state::tracking);
    REQUIRE(fix_st_flags.get_psm_state() == psm_state::tracking);
}

TEST_CASE("fix status flags shall return true when heading of vehicle flag is set otherwise false")
{
    auto fix_st_flags = fix_status_flags
    {
        .head_of_vehicle = true,
    };

    REQUIRE(fix_st_flags.is_head_of_vehicle_valid() == true);
    fix_st_flags.head_of_vehicle = false;
    REQUIRE(fix_st_flags.is_head_of_vehicle_valid() == false);
}

TEST_CASE("fix status flags shall return different values of carrier phase solution status")
{
    auto fix_st_flags = fix_status_flags{};

    fix_st_flags.carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::no_solution);
    REQUIRE(fix_st_flags.get_carrier_phase_solution_status() == carrier_phase_range_solution_status::no_solution);
    fix_st_flags.carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::with_floating_ambiguities);
    REQUIRE(fix_st_flags.get_carrier_phase_solution_status() == carrier_phase_range_solution_status::with_floating_ambiguities);
    fix_st_flags.carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::with_fixed_ambiguities);
    REQUIRE(fix_st_flags.get_carrier_phase_solution_status() == carrier_phase_range_solution_status::with_fixed_ambiguities);
}

TEST_CASE("fix status flags shall be able to be compare")
{
    auto fix_st_flags = fix_status_flags
    {
        .gnss_fix_ok = true,
        .diff_soln = false,
        .psm_state = static_cast<std::uint8_t>(psm_state::not_active),
        .head_of_vehicle = true,
        .carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::no_solution),
    };

    auto fix_st_flags2 = fix_status_flags
    {
        .gnss_fix_ok = true,
        .diff_soln = false,
        .psm_state = static_cast<std::uint8_t>(psm_state::not_active),
        .head_of_vehicle = true,
        .carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::no_solution),
    };

    REQUIRE(fix_st_flags == fix_st_flags2);
}

TEST_CASE("fix status flags shall be able to be check for unequal")
{
    auto fix_st_flags = fix_status_flags
    {
        .gnss_fix_ok = true,
        .diff_soln = false,
        .psm_state = static_cast<std::uint8_t>(psm_state::not_active),
        .head_of_vehicle = true,
        .carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::no_solution),
    };

    auto fix_st_flags2 = fix_status_flags
    {
        .gnss_fix_ok = true,
        .diff_soln = true,
        .psm_state = static_cast<std::uint8_t>(psm_state::not_active),
        .head_of_vehicle = true,
        .carrier_phase_range_solution = static_cast<std::uint8_t>(carrier_phase_range_solution_status::no_solution),
    };

    REQUIRE(fix_st_flags != fix_st_flags2);
}

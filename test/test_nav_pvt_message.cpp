#define CATCH_CONFIG_MAIN
#include "test_raw_messages.hpp"
#include "ubx_nav_pvt_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("The nav_pvt message shall return the iTOW from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_itow() == 674440483);
}

TEST_CASE("The nav_pvt message shall return the year (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_year() == 2022);
}

TEST_CASE("The nav_pvt message shall return the month (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_month() == 1);
}

TEST_CASE("The nav_pvt message shall return the day (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_day() == 10);
}

TEST_CASE("The nav_pvt message shall return the hour (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_hour() == 22);
}

TEST_CASE("The nav_pvt message shall return the min (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_minute() == 48);
}

TEST_CASE("The nav_pvt message shall return the sec (UTC) from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_second() == 51);
}

TEST_CASE("The nav_pvt message shall return the validity flags from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    auto expected_flags = validity_flags{
        .valid_date = true,
        .valid_time = false,
        .fully_resolved = false,
        .valid_msg = true,
    };
    REQUIRE(nav_pvt.get_validity_flags() == expected_flags);
}

TEST_CASE("The nav_pvt message shall return the time accuracy estimate from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_time_accruacy_estimate() == 2);
}

TEST_CASE("The nav_pvt message shall return the fraction of second from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_fraction_of_second() == 44);
}

TEST_CASE("The nav_pvt message shall return the fix status flags from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    auto expected_flags = fix_status_flags{
        .gnss_fix_ok = true,
        .diff_soln = true,
    };
    REQUIRE(nav_pvt.get_fix_status_flags() == expected_flags);
}

TEST_CASE("The nav_pvt message shall return the fix status flags2 from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    auto expected_flags = fix_status_flags2{
        .confirmed_date = true,
        .confirmed_time = true,
    };
    REQUIRE(nav_pvt.get_fix_status_flags2() == expected_flags);
}

TEST_CASE("The nav_pvt message shall return number of satellite from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_number_of_satellites() == 4);
}

TEST_CASE("The nav_pvt message shall return the longitude from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_longitude() == Approx(116.07819f));
}

TEST_CASE("The nav_pvt message shall return the latitude from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_latitude() == Approx(109.38040f));
}

TEST_CASE("The nav_pvt message shall return the height above elliposid from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_height_above_ellipsoid() == 269620246);
}

TEST_CASE("The nav_pvt message shall return the height above mean sea level from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_height_above_mean_sea_level() == 269620246);
}

TEST_CASE("The nav_pvt message shall return the horizontal accuracy estiamte from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_horizontal_accuracy_estimate() == 85);
}

TEST_CASE("The nav_pvt message shall return the vertical accuracy estiamte from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_vertical_accuracy_estimate() == 100);
}

TEST_CASE("The nav_pvt message shall return the NED velocity north from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_ned_velocity_north() == 16);
}

TEST_CASE("The nav_pvt message shall return the NED velocity east from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_ned_velocity_east() == 50);
}

TEST_CASE("The nav_pvt message shall return the NED velocity down from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_ned_velocity_down() == 53);
}

TEST_CASE("The nav_pvt message shall return the ground speed 2-D from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_ground_speed_2d() == 25925);
}

TEST_CASE("The nav_pvt message shall return the heading motion 2-D from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_heading_motion_2d() == Approx(33.68261));
}

TEST_CASE("The nav_pvt message shall return speed accuracy estimate from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_speed_accuracy_estimate() == 132);
}

TEST_CASE("The nav_pvt message shall return heading accuracy estimate from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_heading_accuracy_estimate() == Approx(3359.85234));
}

TEST_CASE("The nav_pvt message shall return position dop from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_position_dop() == Approx(192.35));
}

TEST_CASE("The nav_pvt message shall return fix status flags3 from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    auto expected_flags = fix_status_flags3{
        .invalid_llh = false,
        .last_correction_age = last_correction_age::age_between_10_to_15s,
    };

    REQUIRE(nav_pvt.get_fix_status_flags3() == expected_flags);
}

TEST_CASE("The nav_pvt message shall return heading of vehicle from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_heading_of_vehicle() == Approx(4458.18828));
}

TEST_CASE("The nav_pvt message shall return magnetic declination from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_magnetic_declination() == Approx(68.02));
}

TEST_CASE("The nav_pvt message shall return magnetic declination accuracy from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.get_magnetic_declination_accuracy() == Approx(374.02));
}

TEST_CASE("The nav_pvt message shall be valid when creating from valid data.")
{
    auto nav_pvt = nav_pvt_message{valid_nav_pvt_message.cbegin(), valid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.is_valid() == true);
}

TEST_CASE("The nav_pvt message shall be invalid when creating from a to small payload.")
{
    auto nav_pvt = nav_pvt_message{invalid_nav_pvt_message.cbegin(), invalid_nav_pvt_message.cend()};
    REQUIRE(nav_pvt.is_valid() == false);
}

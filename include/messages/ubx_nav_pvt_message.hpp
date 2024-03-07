// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_NAV_PVT_MESSAGE_HPP
#define UBX_NAV_PVT_MESSAGE_HPP

#include "ubx_fix_status_flags.hpp"
#include "ubx_fix_status_flags2.hpp"
#include "ubx_fix_status_flags3.hpp"
#include "ubx_message.hpp"
#include "ubx_utilities.hpp"
#include "ubx_validity_flags.hpp"
#include <cstdint>
#include <cstring>

namespace ubx
{

enum class fix_type : std::uint8_t
{
    no_fix = 0,
    dead_reckoning_only = 1,
    fix_2d = 2,
    fix_3d = 3,
    gnss = 4,
    time_only = 5,
};

class nav_pvt_message : public message
{
public:
    /**
     * Class ID
     */
    constexpr static std::uint8_t nav_pvt_class_id = 0x01;

    /**
     * Message ID
     */
    constexpr static std::uint8_t nav_pvt_message_id = 0x07;

    /**
     * Message Length
     */
    constexpr static std::uint8_t nav_pvt_length = 0x5C;

    /**
     * Creates a default constructed nav_pvt_message object.
     */
    nav_pvt_message() = default;

    /**
     * Creates a nav_pvt_message object from the raw data.
     * @param begin Start of the raw data.
     * @param end End of the raw data.
     */
    template<typename read_iterator>
    nav_pvt_message(read_iterator const& begin, read_iterator const end);

    /**
     * @return Gives the GPS time of week of the navigation epoch in ms.
     */
    std::uint32_t get_itow() const noexcept;

    /**
     * @return Gives the year (UTC).
     */
    std::uint16_t get_year() const noexcept;

    /**
     * @return Gives the month (UTC). Range from 1 to 12.
     */
    std::uint8_t get_month() const noexcept;

    /**
     * @return Gives the day (UTC). Range from 1 to 31.
     */
    std::uint8_t get_day() const noexcept;

    /**
     * @return Gvies the hour (UTC). Range from 0 to 23.
     */
    std::uint8_t get_hour() const noexcept;

    /**
     * @return Gives the minute (UTC). Range from 0 to 59.
     */
    std::uint8_t get_minute() const noexcept;

    /**
     * @return Gives the scond (UTC). Range from 0 to 59.
     */
    std::uint8_t get_second() const noexcept;

    /**
     * @return Gives the validity flags.
     */
    validity_flags get_validity_flags() const noexcept;

    /**
     * @return Gives the time accruacy estimate in ns.
     */
    std::uint32_t get_time_accruacy_estimate() const noexcept;

    /**
     * @return Gives the fraction of second in ns. Range -1e9 to 1e9.
     */
    std::int32_t get_fraction_of_second() const noexcept;

    /**
     * @return Gives GNSS fix type.
     */
    fix_type get_fix_type() const noexcept;

    /**
     * @return Gives fix status flags.
     */
    fix_status_flags get_fix_status_flags() const noexcept;

    /**
     * @return Gives the fix status flags2.
     */
    fix_status_flags2 get_fix_status_flags2() const noexcept;

    /**
     * @return Gives the number satellites used in the solution.
     */
    std::uint8_t get_number_of_satellites() const noexcept;

    /**
     * @return Gives the longitude in degree.
     */
    float get_longitude() const noexcept;

    /**
     * @return Gives the latitude in degree.
     */
    float get_latitude() const noexcept;

    /**
     * @return Gives the hight above the elliposid in mm.
     */
    std::int32_t get_height_above_ellipsoid() const noexcept;

    /**
     * @return Gives the height above mean seal level in mm.
     */
    std::int32_t get_height_above_mean_sea_level() const noexcept;

    /**
     * @return Gvies the horizontal accuracy estimate in mm.
     */
    std::int32_t get_horizontal_accuracy_estimate() const noexcept;

    /**
     * @return Gives the vertical accuracy estimate in mm.
     */
    std::uint32_t get_vertical_accuracy_estimate() const noexcept;

    /**
     * @return Gives the NED velocity north in mm/s.
     */
    std::int32_t get_ned_velocity_north() const noexcept;

    /**
     * @return Gives the NED velocity east in mm/s.
     */
    std::int32_t get_ned_velocity_east() const noexcept;

    /**
     * @return Gives the NED velocity down in mm/s.
     */
    std::int32_t get_ned_velocity_down() const noexcept;

    /**
     * @return Gives the ground speed 2-D in mm/s.
     */
    std::int32_t get_ground_speed_2d() const noexcept;

    /**
     * @return Gives the heading of motion 2-D in degree.
     */
    float get_heading_motion_2d() const noexcept;

    /**
     * @return Gives the speed accuracy estimate in mm/s.
     */
    std::uint32_t get_speed_accuracy_estimate() const noexcept;

    /**
     * @return Gives the heading accuracy estimate in degree.
     */
    float get_heading_accuracy_estimate() const noexcept;

    /**
     * @return Gives the position DOP.
     */
    float get_position_dop() const noexcept;

    /**
     * @return Gives the fix status flags3.
     */
    fix_status_flags3 const& get_fix_status_flags3() const noexcept;

    /**
     * @return Gives the heading of the vehilce 2-D in degree. This
     * value ins only valid when heading vehicle valid is set.
     * otherwise the value is set to heading of motion.
     */
    float get_heading_of_vehicle() const noexcept;

    /**
     * @return Gives the magnetic declination in degree.
     */
    float get_magnetic_declination() const noexcept;

    /**
     * @return Gives the magnetic declination_accuracy in degree.
     */
    float get_magnetic_declination_accuracy() const noexcept;

private:
    std::uint32_t m_itow{0};
    std::uint16_t m_year{0};
    std::uint8_t m_month{0};
    std::uint8_t m_day{0};
    std::uint8_t m_hour{0};
    std::uint8_t m_minute{0};
    std::uint8_t m_second{0};
    validity_flags m_validity_flags;
    std::uint32_t m_time_accruacy_estimate{0};
    std::int32_t m_fraction_of_second{0};
    fix_type m_fix_type;
    fix_status_flags m_fix_status_flags;
    fix_status_flags2 m_fix_status_flags2;
    std::uint8_t m_number_of_setellites{0};
    float m_longitude{0.0};
    float m_latitude{0.0};
    std::int32_t m_height_above_mean_sea_level{0};
    std::int32_t m_height_above_ellipsoid{0};
    std::int32_t m_horizontal_accuracy_estimate{0};
    std::uint32_t m_vertical_accuracy_estimate{0};
    std::int32_t m_ned_velocity_north{0};
    std::int32_t m_ned_velocity_east{0};
    std::int32_t m_ned_velocity_down{0};
    std::int32_t m_ground_speed_2d{0};
    float m_heading_motion_2d{0};
    std::uint32_t m_speed_accuracy_estimate{0};
    float m_heading_accuracy_estimate{0.0};
    float m_position_dop{0.0};
    fix_status_flags3 m_fix_status_flags3;
    float m_heading_of_vehicle{0.0};
    float m_magnetic_declination{0.0};
    float m_magnetic_declination_accuracy{0};
};

template<typename read_iterator>
nav_pvt_message::nav_pvt_message(read_iterator const& begin, read_iterator const end)
    : message()
{
    static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type, std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if (std::distance(begin, end) < nav_pvt_length) {
        return;
    }

    m_itow = utilities::convert_4byte_to_int<std::uint32_t>(begin[3], begin[2], begin[1], begin[0]);

    m_year = utilities::convert_2byte_to_int<std::uint16_t>(begin[5], begin[4]);
    m_month = begin[6];
    m_day = begin[7];

    m_hour = begin[8];
    m_minute = begin[9];
    m_second = begin[10];

    std::memcpy(&m_validity_flags, &begin[11], sizeof(validity_flags));

    m_time_accruacy_estimate =
        utilities::convert_4byte_to_int<std::uint32_t>(begin[15], begin[14], begin[13], begin[12]);

    m_fraction_of_second = utilities::convert_4byte_to_int<std::int32_t>(begin[19], begin[18], begin[17], begin[16]);

    m_fix_type = static_cast<fix_type>(begin[20]);

    std::memcpy(&m_fix_status_flags, &begin[21], sizeof(fix_status_flags));
    std::memcpy(&m_fix_status_flags2, &begin[22], sizeof(fix_status_flags2));

    m_number_of_setellites = begin[23];

    constexpr auto scaling_factor = 1e-7;
    m_longitude =
        utilities::convert_4byte_to_int<std::int32_t>(begin[27], begin[26], begin[25], begin[24]) * scaling_factor;
    m_latitude =
        utilities::convert_4byte_to_int<std::int32_t>(begin[31], begin[30], begin[29], begin[28]) * scaling_factor;

    m_height_above_ellipsoid =
        utilities::convert_4byte_to_int<std::int32_t>(begin[35], begin[34], begin[33], begin[32]);
    m_height_above_mean_sea_level =
        utilities::convert_4byte_to_int<std::int32_t>(begin[39], begin[38], begin[37], begin[36]);

    m_horizontal_accuracy_estimate =
        utilities::convert_4byte_to_int<std::uint32_t>(begin[43], begin[42], begin[41], begin[40]);
    m_vertical_accuracy_estimate =
        utilities::convert_4byte_to_int<std::uint32_t>(begin[47], begin[46], begin[45], begin[44]);

    m_ned_velocity_north = utilities::convert_4byte_to_int<std::int32_t>(begin[51], begin[50], begin[49], begin[48]);
    m_ned_velocity_east = utilities::convert_4byte_to_int<std::int32_t>(begin[55], begin[54], begin[53], begin[52]);
    m_ned_velocity_down = utilities::convert_4byte_to_int<std::int32_t>(begin[59], begin[58], begin[57], begin[56]);

    m_ground_speed_2d = utilities::convert_4byte_to_int<std::int32_t>(begin[63], begin[62], begin[61], begin[60]);
    constexpr auto heading_scale_factor = 1e-5;
    m_heading_motion_2d = utilities::convert_4byte_to_int<std::int32_t>(begin[67], begin[66], begin[65], begin[64]) *
                          heading_scale_factor;
    m_speed_accuracy_estimate =
        utilities::convert_4byte_to_int<std::uint32_t>(begin[71], begin[70], begin[69], begin[68]);
    m_heading_accuracy_estimate =
        utilities::convert_4byte_to_int<std::uint32_t>(begin[75], begin[74], begin[73], begin[72]) *
        heading_scale_factor;

    constexpr auto postion_dop_scale_factor = 1e-2;
    m_position_dop = utilities::convert_2byte_to_int<std::int16_t>(begin[77], begin[76]) * postion_dop_scale_factor;

    auto fix_status_flags3_raw = utilities::convert_2byte_to_int<std::uint16_t>(begin[79], begin[78]);
    std::memcpy(&m_fix_status_flags3, &fix_status_flags3_raw, sizeof(fix_status_flags3));

    constexpr auto heading_vehicle_scale_factor = 1e-5;
    m_heading_of_vehicle = utilities::convert_4byte_to_int<std::int32_t>(begin[87], begin[86], begin[85], begin[84]) *
                           heading_vehicle_scale_factor;

    constexpr auto magnetic_declination_scale_factor = 1e-2;
    m_magnetic_declination =
        utilities::convert_2byte_to_int<std::int16_t>(begin[89], begin[88]) * magnetic_declination_scale_factor;
    m_magnetic_declination_accuracy =
        utilities::convert_2byte_to_int<std::uint16_t>(begin[91], begin[90]) * magnetic_declination_scale_factor;

    m_status = true;
}

inline std::uint32_t nav_pvt_message::get_itow() const noexcept
{
    return m_itow;
}

inline uint16_t nav_pvt_message::get_year() const noexcept
{
    return m_year;
}

inline uint8_t nav_pvt_message::get_month() const noexcept
{
    return m_month;
}

inline uint8_t nav_pvt_message::get_day() const noexcept
{
    return m_day;
}

inline uint8_t nav_pvt_message::get_hour() const noexcept
{
    return m_hour;
}

inline uint8_t nav_pvt_message::get_minute() const noexcept
{
    return m_minute;
}

inline uint8_t nav_pvt_message::get_second() const noexcept
{
    return m_second;
}

inline validity_flags nav_pvt_message::get_validity_flags() const noexcept
{
    return m_validity_flags;
}

inline uint32_t nav_pvt_message::get_time_accruacy_estimate() const noexcept
{
    return m_time_accruacy_estimate;
}

inline int32_t nav_pvt_message::get_fraction_of_second() const noexcept
{
    return m_fraction_of_second;
}

inline fix_type nav_pvt_message::get_fix_type() const noexcept
{
    return m_fix_type;
}

inline fix_status_flags nav_pvt_message::get_fix_status_flags() const noexcept
{
    return m_fix_status_flags;
}

inline fix_status_flags2 nav_pvt_message::get_fix_status_flags2() const noexcept
{
    return m_fix_status_flags2;
}

inline uint8_t nav_pvt_message::get_number_of_satellites() const noexcept
{
    return m_number_of_setellites;
}

inline float nav_pvt_message::get_longitude() const noexcept
{
    return m_longitude;
}

inline float nav_pvt_message::get_latitude() const noexcept
{
    return m_latitude;
}

inline int32_t nav_pvt_message::get_height_above_ellipsoid() const noexcept
{
    return m_height_above_ellipsoid;
}

inline int32_t nav_pvt_message::get_height_above_mean_sea_level() const noexcept
{
    return m_height_above_mean_sea_level;
}

inline int32_t nav_pvt_message::get_horizontal_accuracy_estimate() const noexcept
{
    return m_horizontal_accuracy_estimate;
}

inline uint32_t nav_pvt_message::get_vertical_accuracy_estimate() const noexcept
{
    return m_vertical_accuracy_estimate;
}

inline int32_t nav_pvt_message::get_ned_velocity_north() const noexcept
{
    return m_ned_velocity_north;
}

inline int32_t nav_pvt_message::get_ned_velocity_east() const noexcept
{
    return m_ned_velocity_east;
}

inline int32_t nav_pvt_message::get_ned_velocity_down() const noexcept
{
    return m_ned_velocity_down;
}

inline int32_t nav_pvt_message::get_ground_speed_2d() const noexcept
{
    return m_ground_speed_2d;
}

inline float nav_pvt_message::get_heading_motion_2d() const noexcept
{
    return m_heading_motion_2d;
}

inline uint32_t nav_pvt_message::get_speed_accuracy_estimate() const noexcept
{
    return m_speed_accuracy_estimate;
}

inline float nav_pvt_message::get_heading_accuracy_estimate() const noexcept
{
    return m_heading_accuracy_estimate;
}

inline float nav_pvt_message::get_position_dop() const noexcept
{
    return m_position_dop;
}

inline fix_status_flags3 const& nav_pvt_message::get_fix_status_flags3() const noexcept
{
    return m_fix_status_flags3;
}

inline float nav_pvt_message::get_heading_of_vehicle() const noexcept
{
    return m_heading_of_vehicle;
}

inline float nav_pvt_message::get_magnetic_declination() const noexcept
{
    return m_magnetic_declination;
}

inline float nav_pvt_message::get_magnetic_declination_accuracy() const noexcept
{
    return m_magnetic_declination_accuracy;
}

} // namespace ubx

#endif // UBX_NAV_PVT_MESSAGE_HPP

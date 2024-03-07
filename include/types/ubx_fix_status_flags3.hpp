// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_FIX_STATUS_FLAGS3_HPP
#define UBX_FIX_STATUS_FLAGS3_HPP

#include <cstdint>

namespace ubx
{

/**
 * Values for the last correction age.
 */
enum last_correction_age : std::uint8_t
{
    not_available = 0,
    age_between_0_to_1s = 1,
    age_between_1_to_2s = 2,
    age_between_2_to_5s = 3,
    age_between_5_to_10s = 4,
    age_between_10_to_15s = 5,
    age_between_15_to_20s = 6,
    age_between_20_to_30s = 7,
    age_between_30_to_45s = 8,
    age_between_45_to_60s = 9,
    age_between_60_to_90s = 10,
    age_greater_than_120s = 11,
};

/**
 * fix status flags3 of the nav-pvt message.
 */
struct fix_status_flags3
{
    std::uint16_t invalid_llh : 1;
    std::uint16_t last_correction_age : 4;
    std::uint16_t reserved : 11;

    /**
     * @return True longitue latitude, height and hMSL are invalid otherwise false.
     */
    bool is_llh_invalid() const noexcept;

    /**
     * @return The age of most recently received differential correction.
     */
    enum last_correction_age get_last_correction_age() const noexcept;

    /**
     * Equal operator resvered values are ignored.
     * @param lhs left hand side fix status flags3.
     * @param rhs right hande side fix status flags3.
     * @return true both are the same otherwise false.
     */
    friend bool operator==(fix_status_flags3 const& lhs, fix_status_flags3 const& rhs);

    /**
     * Unequal operator resvered values are ignored.
     * @param lhs left hand side fix status flags3.
     * @param rhs right hande side fix status flags3.
     * @return true both are the not equal, otherwise false.
     */
    friend bool operator!=(fix_status_flags3 const& lhs, fix_status_flags3 const& rhs);
} __attribute__((packed));

inline bool fix_status_flags3::is_llh_invalid() const noexcept
{
    return invalid_llh;
}

inline enum last_correction_age fix_status_flags3::get_last_correction_age() const noexcept
{
    return static_cast<enum last_correction_age>(last_correction_age);
}

inline bool operator==(fix_status_flags3 const& lhs, fix_status_flags3 const& rhs)
{
    // clang-format off
    return ((lhs.invalid_llh == rhs.invalid_llh) &&
            (lhs.last_correction_age == rhs.last_correction_age));
    // clang-format on
}

inline bool operator!=(fix_status_flags3 const& lhs, fix_status_flags3 const& rhs)
{
    return !(lhs == rhs);
}

} // namespace ubx

#endif // UBX_FIX_STATUS_FLAGS3_HPP

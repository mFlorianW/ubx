// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_FIX_STATUS_FLAGS_HPP
#define UBX_FIX_STATUS_FLAGS_HPP

#include "ubx_types.hpp"
#include <cstdint>

namespace ubx
{

enum class psm_state : std::uint8_t
{
    not_active = 0,
    enabled = 1,
    acquisition = 2,
    tracking = 3,
    power_optimized_tracking = 4,
    inactive = 5,
};

enum class carrier_phase_range_solution_status
{
    no_solution = 0,
    with_floating_ambiguities = 1,
    with_fixed_ambiguities = 2,
};

/**
 * fix status flags of the nav-pvt message.
 */
struct fix_status_flags
{
    std::uint8_t gnss_fix_ok : 1;
    std::uint8_t diff_soln : 1;
    std::uint8_t psm_state : 3;
    std::uint8_t head_of_vehicle : 1;
    std::uint8_t carrier_phase_range_solution : 2;

    /**
     * @return Checks if the gnss fix ok flag is.
     *         True flag is set otherwise false.
     */
    bool is_gnss_fix_ok() const noexcept;

    /**
     * @return Gives status about if the differential corrections were applied.
     *         True means correction was applied otherwise false.
     */
    bool is_diff_soln_applied() const noexcept;

    /**
     * @return Gives the power save mode state.
     */
    enum psm_state get_psm_state() const noexcept;

    /**
     * @return Checks if the head of vehilce flag is set.
     *         True is set otherwise false.
     */
    bool is_head_of_vehicle_valid() const noexcept;

    /**
     * @return Gives the status about carrier phase range solution.
     */
    carrier_phase_range_solution_status get_carrier_phase_solution_status() const noexcept;

    /**
     * Equal operator resvered values are ignored.
     * @param lhs left hand side fix status flags.
     * @param rhs right hande side fix status flags.
     * @return true both are the same otherwise false.
     */
    friend bool operator==(fix_status_flags const& lhs, fix_status_flags const& rhs);

    /**
     * Unequal operator resvered values are ignored.
     * @param lhs left hand side fix status flags.
     * @param rhs right hande side fix status flags.
     * @return true both are the not equal, otherwise false.
     */
    friend bool operator!=(fix_status_flags const& lhs, fix_status_flags const& rhs);
} __attribute__((packed));

inline bool fix_status_flags::is_gnss_fix_ok() const noexcept
{
    return gnss_fix_ok;
}

inline bool fix_status_flags::is_diff_soln_applied() const noexcept
{
    return diff_soln;
}

inline enum psm_state fix_status_flags::get_psm_state() const noexcept
{
    return static_cast<enum psm_state>(psm_state);
}

inline bool fix_status_flags::is_head_of_vehicle_valid() const noexcept
{
    return head_of_vehicle;
}

inline carrier_phase_range_solution_status fix_status_flags::get_carrier_phase_solution_status() const noexcept
{
    return static_cast<carrier_phase_range_solution_status>(carrier_phase_range_solution);
}

inline bool operator==(fix_status_flags const& lhs, fix_status_flags const& rhs)
{
    // clang-format off
    return ((lhs.gnss_fix_ok == rhs.gnss_fix_ok) &&
            (lhs.diff_soln == rhs.diff_soln) &&
            (lhs.psm_state == rhs.psm_state) &&
            (lhs.head_of_vehicle == rhs.head_of_vehicle) &&
            (lhs.carrier_phase_range_solution == rhs.carrier_phase_range_solution));
    //clang-format on
}

inline bool operator!=(const fix_status_flags &lhs, const fix_status_flags &rhs)
{
    return !(lhs == rhs);
}

} //namespace ubx

#endif // FIX_STATUS_FLAGS_HPP

#ifndef UBX_FIX_STATUS_FLAGS2_HPP
#define UBX_FIX_STATUS_FLAGS2_HPP

#include <cstdint>

namespace ubx
{

/**
 * fix status flags2 of the nav-pvt message.
 */
struct fix_status_flags2
{
    std::uint8_t resevered : 5;
    std::uint8_t confirmed_available : 1;
    std::uint8_t confirmed_date : 1;
    std::uint8_t confirmed_time : 1;

    /**
     * @return True UTC date and Time of day validity is available otherwise false.
     */
    bool is_confirmed_available() const noexcept;

    /**
     * @return True the UTC date validity could be confirmed otherwise false.
     */
    bool is_date_confirmed();

    /**
     * @return True the UTC time of day validity could be confirmed otherwise false.
     */
    bool is_time_confirmed();

    /**
     * Equal operator resvered values are ignored.
     * @param lhs left hand side fix status flags2.
     * @param rhs right hande side fix status flags2.
     * @return true both are the same otherwise false.
     */
    friend bool operator==(fix_status_flags2 const& lhs, fix_status_flags2 const& rhs);

    /**
     * Unequal operator resvered values are ignored.
     * @param lhs left hand side fix status flags2.
     * @param rhs right hande side fix status flags2.
     * @return true both are the not equal, otherwise false.
     */
    friend bool operator!=(fix_status_flags2 const& lhs, fix_status_flags2 const& rhs);
} __attribute__((packed));

inline bool fix_status_flags2::is_confirmed_available() const noexcept
{
    return confirmed_available;
}

inline bool fix_status_flags2::is_date_confirmed()
{
    return confirmed_date;
}

inline bool fix_status_flags2::is_time_confirmed()
{
    return confirmed_time;
}

inline bool operator==(fix_status_flags2 const& lhs, fix_status_flags2 const& rhs)
{
    // clang-format off
    return ((lhs.confirmed_available == rhs.confirmed_available) &&
            (lhs.confirmed_date == rhs.confirmed_date) &&
            (lhs.confirmed_time == rhs.confirmed_time));
    // clang-format on
}

inline bool operator!=(fix_status_flags2 const& lhs, fix_status_flags2 const& rhs)
{
    return !(lhs == rhs);
}

} // namespace ubx

#endif // UBX_FIX_STATUS_FLAGS2_HPP

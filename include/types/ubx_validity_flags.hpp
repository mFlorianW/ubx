#ifndef UBX_VALIDITY_FLAGS_HPP
#define UBX_VALIDITY_FLAGS_HPP

#include <cstdint>

namespace ubx
{
struct validity_flags
{
    std::uint8_t valid_date:1;
    std::uint8_t valid_time:1;
    std::uint8_t fully_resolved:1;
    std::uint8_t valid_msg:1;
    std::uint8_t reserved:4;

    /**
     * @return True valid date flag is set otherwise false.
     */
    bool is_date_valid() const noexcept;

    /**
     * @return True valid time flag is set otherwise false.
     */
    bool is_time_valid() const noexcept;

    /**
     * @return True full resolved flag is set otherwise false.
     */
    bool is_fully_resolved() const noexcept;

    /**
     * @return True valid message flag is set ohterwise false.
     */
    bool is_msg_valid() const noexcept;

    /**
     * Equal operator resvered values are ignored.
     * @param lhs left hand side validity flags.
     * @param rhs right hande side validity flags.
     * @return true both are the same otherwise false.
     */
    friend bool operator==(const validity_flags &lhs, const validity_flags &rhs);

    /**
     * Unequal operator resvered values are ignored.
     * @param lhs left hand side validity flags.
     * @param rhs right hande side validity flags.
     * @return true both are the not equal, otherwise false.
     */
    friend bool operator!=(const validity_flags &lhs, const validity_flags &rhs);
};

inline bool validity_flags::is_date_valid() const noexcept
{
    return valid_date;
}

inline bool validity_flags::is_time_valid() const noexcept
{
    return valid_time;
}

inline bool validity_flags::is_fully_resolved() const noexcept
{
    return fully_resolved;
}

inline bool validity_flags::is_msg_valid() const noexcept
{
    return valid_msg;
}

bool operator==(const validity_flags &lhs, const validity_flags &rhs)
{
    return ((lhs.valid_date == rhs.valid_date) &&
            (lhs.valid_time == rhs.valid_time) &&
            (lhs.fully_resolved == rhs.fully_resolved) &&
            (lhs.valid_msg == rhs.valid_msg));
}

bool operator!=(const validity_flags &lhs, const validity_flags &rhs)
{
    return !(lhs == rhs);
}

}

#endif // UBX_VALIDITY_FLAGS_HPP

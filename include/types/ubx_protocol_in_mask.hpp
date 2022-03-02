#ifndef UBX_PROTOCOL_IN_MASK_HPP
#define UBX_PROTOCOL_IN_MASK_HPP

#include <cstdint>

namespace ubx
{

struct protocol_in_mask
{
    std::uint16_t ubx_in : 1;
    std::uint16_t nema_in : 1;
    std::uint16_t rtcm_in : 1;
    std::uint16_t reseverd1 : 2;
    std::uint16_t rtcm3_in : 1;
    std::uint16_t reserverd2 : 10;

    bool is_ubx_in_enabled() const noexcept;

    bool is_nema_in_enabled() const noexcept;

    bool is_rtcm_in_enabled() const noexcept;

    bool is_rtcm3_in_enabled() const noexcept;

    friend bool operator==(const protocol_in_mask &mask1, const protocol_in_mask &mask2);
    friend bool operator!=(const protocol_in_mask &mask1, const protocol_in_mask &mask2);

} __attribute__((packed));

inline bool protocol_in_mask::is_ubx_in_enabled() const noexcept
{
    return ubx_in;
}

inline bool protocol_in_mask::is_nema_in_enabled() const noexcept
{
    return nema_in;
}

inline bool protocol_in_mask::is_rtcm_in_enabled() const noexcept
{
    return rtcm_in;
}

inline bool protocol_in_mask::is_rtcm3_in_enabled() const noexcept
{
    return rtcm3_in;
}

inline bool operator==(const protocol_in_mask &mask1, const protocol_in_mask &mask2)
{
    // clang-format off
    return ((mask1.ubx_in == mask2.ubx_in) &&
            (mask1.nema_in == mask2.nema_in) &&
            (mask1.rtcm_in == mask2.rtcm_in) &&
            (mask1.rtcm3_in == mask2.rtcm3_in));
    // clang-format on
}

inline bool operator!=(const protocol_in_mask &mask1, const protocol_in_mask &mask2)
{
    return !(mask1 == mask2);
}

} // namespace ubx

#endif // UBX_PROTOCOL_MASK_HPP

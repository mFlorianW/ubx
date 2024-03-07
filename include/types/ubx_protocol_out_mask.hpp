#ifndef UBX_PROTOCOL_OUT_MASK_HPP
#define UBX_PROTOCOL_OUT_MASK_HPP

#include <cstdint>

namespace ubx
{

struct protocol_out_mask
{
    std::uint32_t ubx_out : 1;
    std::uint32_t nmea_out : 1;
    std::uint16_t reseverd_1 : 3;
    std::uint16_t rtcm3_out : 1;
    std::uint16_t reseverd_2 : 9;

    bool is_ubx_out_enabled() const noexcept;

    bool is_nmea_out_enabled() const noexcept;

    bool is_rtcm3_out_enabled() const noexcept;

    friend bool operator==(protocol_out_mask const& mask1, protocol_out_mask const& mask2);
    friend bool operator!=(protocol_out_mask const& mask1, protocol_out_mask const& mask2);

} __attribute__((packed));

inline bool protocol_out_mask::is_ubx_out_enabled() const noexcept
{
    return ubx_out;
}

inline bool protocol_out_mask::is_nmea_out_enabled() const noexcept
{
    return nmea_out;
}

inline bool protocol_out_mask::is_rtcm3_out_enabled() const noexcept
{
    return rtcm3_out;
}

inline bool operator==(protocol_out_mask const& mask1, protocol_out_mask const& mask2)
{
    // clang-format off
    //resevered parts are ignored
    return ((mask1.ubx_out == mask2.ubx_out) &&
            (mask1.nmea_out == mask2.nmea_out) &&
            (mask1.rtcm3_out == mask2.rtcm3_out));
    // clang-format on
}

inline bool operator!=(protocol_out_mask const& mask1, protocol_out_mask const& mask2)
{
    return !(mask1 == mask2);
}

} // namespace ubx

#endif // UBX_PROTOCOL_OUT_MASK_HPP

#include "ubx_utilities.hpp"

namespace ubx::utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte,
                         std::uint8_t low_byte)
{
    return (high_byte << 8) | low_byte;
}

std::uint32_t get_uint32(std::uint8_t fourth_byte,
                         std::uint8_t third_byte,
                         std::uint8_t second_byte,
                         std::uint8_t first_byte)
{
    return fourth_byte << 24 |
           third_byte << 16 |
           second_byte << 8 |
           first_byte;
}

} /* namespace Ubx::Utilities */

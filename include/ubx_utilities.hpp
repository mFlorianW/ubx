#ifndef UBXUTILITIES_H
#define UBXUTILITIES_H

#include <cstdint>

namespace ubx::utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte,
                         std::uint8_t low_byte);

std::uint32_t get_uint32(std::uint8_t fourth_byte,
                         std::uint8_t third_byte,
                         std::uint8_t second_byte,
                         std::uint8_t first_byte);

} /* namespace Ubx::Utilities */

#endif // UBXUTILITIES_H

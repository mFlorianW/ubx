#ifndef UBXUTILITIES_H
#define UBXUTILITIES_H

#include <cstdint>

namespace Ubx::Utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte, std::uint8_t low_byte);

} /* namespace Ubx::Utilities */

#endif // UBXUTILITIES_H

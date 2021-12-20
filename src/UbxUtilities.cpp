#include "UbxUtilities.hpp"

namespace ubx::utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte, std::uint8_t low_byte)
{
    return (high_byte << 8) | low_byte;
}

} /* namespace Ubx::Utilities */

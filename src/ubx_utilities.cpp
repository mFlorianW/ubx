// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ubx_utilities.hpp"

namespace ubx::utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte, std::uint8_t low_byte)
{
    return (high_byte << 8) | low_byte;
}

} // namespace ubx::utilities

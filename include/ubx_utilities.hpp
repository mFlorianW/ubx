// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBXUTILITIES_H
#define UBXUTILITIES_H

#include <cstdint>
#include <cstdlib>
#include <optional>

namespace ubx::utilities
{

template<typename T>
T convert_2byte_to_int(std::uint8_t high_byte, std::uint8_t low_byte)
{
    static_assert(std::is_same_v<T, std::uint16_t> || std::is_same_v<T, std::int16_t>,
                  "Only allowed values are std::uint32 or std::int32");
    return (high_byte << 8) | low_byte;
}

template<typename T>
T convert_4byte_to_int(std::uint8_t fourth_byte,
                       std::uint8_t third_byte,
                       std::uint8_t second_byte,
                       std::uint8_t first_byte)
{
    static_assert(std::is_same_v<T, std::uint32_t> || std::is_same_v<T, std::int32_t>,
                  "Only allowed values are std::uint32 or std::int32");

    return fourth_byte << 24 | third_byte << 16 | second_byte << 8 | first_byte;
}

struct checksum_result
{
    std::uint8_t ck_a{0};
    std::uint8_t ck_b{0};
};

template<typename read_iterator>
checksum_result calculate_checksum(read_iterator const& checksum_begin, size_t checksum_length)
{
    std::uint16_t ck_a = 0;
    std::uint16_t ck_b = 0;

    for (size_t i = 0; i < checksum_length; ++i) {
        ck_a = ck_a + checksum_begin[i];
        ck_b = ck_b + ck_a;
    }

    ck_a = ck_a & 0xFF;
    ck_b = ck_b & 0xFF;

    return checksum_result{
        .ck_a = static_cast<std::uint8_t>(ck_a),
        .ck_b = static_cast<std::uint8_t>(ck_b),
    };
}

} // namespace ubx::utilities

#endif // UBXUTILITIES_H

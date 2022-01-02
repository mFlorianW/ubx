#ifndef UBXUTILITIES_H
#define UBXUTILITIES_H

#include <cstdint>
#include <optional>
#include <cstdlib>

namespace ubx::utilities
{

std::uint16_t get_uint16(std::uint8_t high_byte,
                         std::uint8_t low_byte);

std::uint32_t get_uint32(std::uint8_t fourth_byte,
                         std::uint8_t third_byte,
                         std::uint8_t second_byte,
                         std::uint8_t first_byte);

struct checksum_result
{
    std::uint8_t ck_a{0};
    std::uint8_t ck_b{0};
};

template<typename read_iterator>
checksum_result calculate_checksum(const read_iterator &checksum_begin, size_t checksum_length)
{
    std::uint16_t ck_a = 0;
    std::uint16_t ck_b = 0;

    for(size_t i = 0; i < checksum_length;  ++i)
    {
        ck_a = ck_a + checksum_begin[i];
        ck_b = ck_b + ck_a;
    }

    ck_a = ck_a & 0xFF;
    ck_b = ck_b & 0xFF;

    return checksum_result
    {
        .ck_a = static_cast<std::uint8_t>(ck_a),
        .ck_b = static_cast<std::uint8_t>(ck_b),
    };
}

} /* namespace Ubx::Utilities */

#endif // UBXUTILITIES_H

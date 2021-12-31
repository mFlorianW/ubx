#ifndef UBX_FRAME_FACTORY_HPP
#define UBX_FRAME_FACTORY_HPP

#include "ubx_utilities.hpp"
#include <cstdint>
#include <cstring>
#include <iterator>
#include <array>

namespace ubx::frame_factory
{

template<typename write_iterator, typename read_iterator>
bool create_frame(std::int8_t class_id,
                  std::uint8_t message_id,
                  const read_iterator &payload_begin,
                  const read_iterator &payload_end,
                  write_iterator frame_begin,
                  write_iterator frame_end)
{
    //put preamble
    frame_begin[0] = 0x5b;
    frame_begin[1] = 0x62;
    frame_begin[2] = class_id;
    frame_begin[3] = message_id;

    //put payload length
    auto payload_length_raw = static_cast<std::uint16_t>(std::distance(payload_begin, payload_end));
    auto payload_length = std::array<std::uint8_t,2>{};
    std::memcpy(&payload_length[0], &payload_length_raw, payload_length.size());

    frame_begin[4] = payload_length[0];
    frame_begin[5] = payload_length[1];

    //put payload
    constexpr auto payload_index_begin = static_cast<std::uint16_t>(6);
    auto payload_index = static_cast<std::uint16_t>(0);
    auto payload_end_index = static_cast<std::uint16_t>(payload_index_begin + payload_length_raw);
    for(std::uint16_t i = payload_index_begin; i < payload_end_index ; ++i)
    {
        frame_begin[i] = payload_begin[payload_index];
        ++payload_index;
    }

    constexpr size_t constant_checksum_length = 4;
    size_t checksum_length = constant_checksum_length + payload_length_raw;
    const auto checksum_result = utilities::calculate_checksum(frame_begin + 2, checksum_length);

    frame_begin[6 + payload_length_raw] = checksum_result.ck_a;
    frame_begin[6 + payload_length_raw + 1] = checksum_result.ck_b;

    return false;
}

} //namespace ubx

#endif // UBX_FRAME_FACTORY_HPP

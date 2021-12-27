#ifndef TEST_RAW_MESSAGES_HPP
#define TEST_RAW_MESSAGES_HPP

#include <cstdint>
#include <array>

namespace ubx
{

constexpr std::array<std::uint8_t, 2> valid_ack_msg =
{
    0x20, 0x10
};

constexpr std::array<std::uint8_t, 1> invalid_ack_msg =
{
    0x20
};


}

#endif // TEST_RAW_MESSAGES_HPP

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

constexpr std::array<std::uint8_t, 20> valid_uart_port_config =
{
    0x01, // port id
    0x00, // resevered
    0x2b, 0x02, // TX ready bit field
    0x80, 0x08, 0x00, 0x00, // UART mode in little endian
    0x00, 0xc2, 0x01, 0x00, // UART baudrate in little endian
    0x03, 0x00, //in protocol mask
    0x03, 0x00, //out protocol mask
    0x02, 0x00, //flags
    0x00, 0x00 // reserved two bytes
};

constexpr std::array<std::uint8_t, 19> invalid_uart_port_config =
{
    0x01, // port id
    0x00, // resevered
    0x2b,
    0x02, // TX ready bit field
    0x80, 0x08, 0x00, // UART mode in little endian
    0x00, 0xc2, 0x01, 0x00, // UART baudrate in little endian
    0x03, 0x00, //in protocol mask
    0x03, 0x00, //out protocol mask
    0x02, 0x00, //flags
    0x00, 0x00 // reserved two bytes
};

constexpr std::array<std::uint8_t, 3> valid_message_configuration =
{
    0x27, //class id
    0x20, //message id
    0x05, //rate
};

constexpr std::array<std::uint8_t, 2> invalid_message_configuration =
{
    0x27, //class id
    0x20, //message id
};

} // namespace ubx;

#endif // TEST_RAW_MESSAGES_HPP

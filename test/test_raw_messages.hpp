#ifndef TEST_RAW_MESSAGES_HPP
#define TEST_RAW_MESSAGES_HPP

#include <array>
#include <cstdint>

namespace ubx
{

constexpr std::array<std::uint8_t, 2> valid_ack_msg = {0x20, 0x10};

constexpr std::array<std::uint8_t, 1> invalid_ack_msg = {0x20};

constexpr std::array<std::uint8_t, 20> valid_uart_port_config = {
    0x01, // port id
    0x00, // resevered
    0x2b, 0x02, // TX ready bit field
    0x80, 0x08, 0x00, 0x00, // UART mode in little endian
    0x00, 0xc2, 0x01, 0x00, // UART baudrate in little endian
    0x03, 0x00, // in protocol mask
    0x03, 0x00, // out protocol mask
    0x02, 0x00, // flags
    0x00, 0x00 // reserved two bytes
};

constexpr std::array<std::uint8_t, 19> invalid_uart_port_config = {
    0x01, // port id
    0x00, // resevered
    0x2b,
    0x02, // TX ready bit field
    0x80,
    0x08,
    0x00, // UART mode in little endian
    0x00,
    0xc2,
    0x01,
    0x00, // UART baudrate in little endian
    0x03,
    0x00, // in protocol mask
    0x03,
    0x00, // out protocol mask
    0x02,
    0x00, // flags
    0x00,
    0x00 // reserved two bytes
};

constexpr std::array<std::uint8_t, 3> valid_message_configuration = {
    0x27, // class id
    0x20, // message id
    0x05, // rate
};

constexpr std::array<std::uint8_t, 2> invalid_message_configuration = {
    0x27, // class id
    0x20, // message id
};

constexpr std::array<std::uint8_t, 3> valid_message_configuration_poll = {
    0x27, // class id
    0x20, // message id
};

constexpr std::array<std::uint8_t, 92> valid_nav_pvt_message = {
    0x23, 0x025, 0x33, 0x28, // iTOW
    0xe6, 0x07, // year (UTC) 2022
    0x01, // month January
    0x0A, // day 10
    0x16, // hour 22
    0x30, // minute 48
    0x33, // second 51
    0x09, // validity flgas: validDate = True, validTime =false, fullResolved = false, validMsg = True,
    0x02, 0x00,  0x00, 0x00, // time accruacy estimate in ns. 2ns
    0x2c, 0x00,  0x00, 0x00, // fraction of second 44ns
    0x03, // fixType 3D-fix
    0x03, // fix status flags
    0xC0, // fix status flags2
    0x04, // number of satellites
    0x15, 0x20,  0x30, 0x45, // longitude
    0x15, 0x20,  0x32, 0x41, // latitude
    0x16, 0x14,  0x12, 0x10, // height above ellipsoid
    0x16, 0x14,  0x12, 0x10, // height above mean seal level
    0x55, 0x00,  0x00, 0x00, // horizonal accuracy estimate
    0x64, 0x00,  0x00, 0x00, // vertical accuracy estimate
    0x10, 0x00,  0x00, 0x00, // ned velocity north
    0x32, 0x00,  0x00, 0x00, // ned velocity east
    0x35, 0x00,  0x00, 0x00, // ned velocity east
    0x45, 0x65,  0x00, 0x00, // ground speed 2d
    0x45, 0x65,  0x33, 0x00, // heading of motion 2d
    0x84, 0x00,  0x00, 0x00, // speed accuracy estimate
    0x52, 0xBA,  0x06, 0x14, // heading accuracy estimate
    0x23, 0x4B, // position DOP
    0x0A, 0x00, // fix status flag3
    0x00, 0x00,  0x00, 0x00, // reserved bytes
    0xCC, 0xA7,  0x92, 0x1A, // heading vehicle
    0x92, 0x1A, // magnetic declination
    0x1A, 0x92, // magnetic declination accuracy
};

constexpr std::array<std::uint8_t, 0> invalid_nav_pvt_message = {};

} // namespace ubx

#endif // TEST_RAW_MESSAGES_HPP

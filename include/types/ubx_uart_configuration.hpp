#ifndef UBX_UART_CONFIGRATION_HPP
#define UBX_UART_CONFIGRATION_HPP

#include <cstdint>

namespace ubx
{

enum class data_length : std::uint8_t
{
    bit5 = 0x00, // not supported
    bit6 = 0x01, // not supported
    bit7 = 0x02, // supported only with paritiy
    bit8 = 0x03,
};

enum class parity : std::uint8_t
{
    even_parity = 0x00,
    odd_parity = 0x01,
    no_parity = 0x04,
};

enum class stop_bits
{
    one_stop_bit = 0x00,
    one_and_half_stop_bit = 0x01,
    two_stop_bits = 0x02,
    half_stop_bit = 0x03,
};

struct uart_configuration
{
    std::uint32_t reserved : 6;
    std::uint32_t data_length : 2;
    std::uint32_t reserved_1 : 1;
    std::uint32_t parity : 3;
    std::uint32_t stop_bits : 2;
    std::uint32_t reserved_2 : 18;

    ubx::data_length get_data_length() const noexcept;

    ubx::parity get_paritiy() const noexcept;

    ubx::stop_bits get_stop_bits() const noexcept;

    friend bool operator==(const uart_configuration &cfg1, const uart_configuration &cfg2);
    friend bool operator!=(const uart_configuration &cfg1, const uart_configuration &cfg2);

} __attribute__((packed));

inline ubx::data_length uart_configuration::get_data_length() const noexcept
{
    return static_cast<ubx::data_length>(data_length);
}

inline ubx::parity uart_configuration::get_paritiy() const noexcept
{
    return static_cast<ubx::parity>(parity);
}

inline ubx::stop_bits uart_configuration::get_stop_bits() const noexcept
{
    return static_cast<ubx::stop_bits>(stop_bits);
}

inline bool operator==(const uart_configuration &cfg1, const uart_configuration &cfg2)
{
    // clang-format off
    // The reservered areas are ignored.
    return (cfg1.data_length == cfg2.data_length &&
            cfg1.parity == cfg2.parity &&
            cfg1.stop_bits == cfg2.stop_bits);
    // clang-format on
}

inline bool operator!=(const uart_configuration &cfg1, const uart_configuration &cfg2)
{
    return !(cfg1 == cfg2);
}

} // namespace ubx

#endif // UBX_UART_CONFIGRATION_HPP

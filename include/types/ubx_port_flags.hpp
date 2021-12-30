#ifndef UBX_UART_FLAGS_HPP
#define UBX_UART_FLAGS_HPP

#include <cstdint>

namespace ubx
{
struct port_flags
{
    std::uint16_t reseverd1:1;
    std::uint16_t extended_tx_timeout:1;
    std::uint16_t reseverd2:14;

    bool is_extended_tx_timeout_enabled() const noexcept;

    friend bool operator==(const port_flags &flags1, const port_flags &flags2);
    friend bool operator!=(const port_flags &flags1, const port_flags &flags2);

} __attribute__((packed));

inline bool port_flags::is_extended_tx_timeout_enabled() const noexcept
{
    return extended_tx_timeout;
}

bool operator==(const port_flags &flags1, const port_flags &flags2)
{
    //resevered parts are ignored.
    return flags1.extended_tx_timeout == flags2.extended_tx_timeout;
}
bool operator!=(const port_flags &flags1, const port_flags &flags2)
{
    return !(flags1 == flags2);
}

} //namespace

#endif // UBX_UART_FLAGS_HPP

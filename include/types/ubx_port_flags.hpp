// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_UART_FLAGS_HPP
#define UBX_UART_FLAGS_HPP

#include <cstdint>

namespace ubx
{
struct port_flags
{
    std::uint16_t reseverd1 : 1;
    std::uint16_t extended_tx_timeout : 1;
    std::uint16_t reseverd2 : 14;

    bool is_extended_tx_timeout_enabled() const noexcept;

    friend bool operator==(port_flags const& flags1, port_flags const& flags2);
    friend bool operator!=(port_flags const& flags1, port_flags const& flags2);

} __attribute__((packed));

inline bool port_flags::is_extended_tx_timeout_enabled() const noexcept
{
    return extended_tx_timeout;
}

inline bool operator==(port_flags const& flags1, port_flags const& flags2)
{
    // resevered parts are ignored.
    return flags1.extended_tx_timeout == flags2.extended_tx_timeout;
}
inline bool operator!=(port_flags const& flags1, port_flags const& flags2)
{
    return !(flags1 == flags2);
}

} // namespace ubx

#endif // UBX_UART_FLAGS_HPP

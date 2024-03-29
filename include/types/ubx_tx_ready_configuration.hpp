// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_TX_READY_CONFIGURATION_HPP
#define UBX_TX_READY_CONFIGURATION_HPP

#include <cstdint>

struct tx_ready_configuration
{
    std::uint16_t enabled : 1;
    std::uint16_t polarity : 1;
    std::uint16_t pin : 5;
    std::uint16_t threshold : 9;

    friend bool operator==(tx_ready_configuration const& cfg1, tx_ready_configuration const& cfg2);
    friend bool operator!=(tx_ready_configuration const& cfg1, tx_ready_configuration const& cfg2);
} __attribute__((packed));

inline bool operator==(tx_ready_configuration const& cfg1, tx_ready_configuration const& cfg2)
{
    // clang-format off
    return (cfg1.enabled == cfg2.enabled &&
            cfg1.polarity == cfg2.polarity &&
            cfg1.pin == cfg2.pin &&
            cfg1.threshold == cfg2.threshold);
    // clang-format on
}

inline bool operator!=(tx_ready_configuration const& cfg1, tx_ready_configuration const& cfg2)
{
    return !(cfg1 == cfg2);
}

#endif // UBX_TX_READY_CONFIGURATION_HPP

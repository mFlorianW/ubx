#ifndef UBX_TX_READY_CONFIGURATION_HPP
#define UBX_TX_READY_CONFIGURATION_HPP

#include <cstdint>

struct tx_ready_configuration
{
    std::uint16_t enabled:1;
    std::uint16_t polarity:1;
    std::uint16_t pin:5;
    std::uint16_t threshold:9;

    friend bool operator== (const tx_ready_configuration& cfg1, const tx_ready_configuration& cfg2);
    friend bool operator!= (const tx_ready_configuration& cfg1, const tx_ready_configuration& cfg2);
} __attribute__((packed));

bool operator==(const tx_ready_configuration& cfg1, const tx_ready_configuration& cfg2)
{
    return (cfg1.enabled == cfg2.enabled &&
            cfg1.polarity == cfg2.polarity &&
            cfg1.pin == cfg2.pin &&
            cfg1.threshold == cfg2.threshold);
}

bool operator!=(const tx_ready_configuration& cfg1, const tx_ready_configuration& cfg2)
{
    return !(cfg1 == cfg2);
}

#endif // UBX_TX_READY_CONFIGURATION_HPP

#ifndef UBX_UART_PORT_CONFIGURATION_MESSAGE_HPP
#define UBX_UART_PORT_CONFIGURATION_MESSAGE_HPP

#include "ubx_ack_message.hpp"
#include "ubx_types.hpp"
#include "ubx_tx_ready_configuration.hpp"
#include "ubx_utilities.hpp"
#include "ubx_uart_configuration.hpp"
#include "ubx_protocol_in_mask.hpp"
#include "ubx_protocol_out_mask.hpp"
#include "ubx_port_flags.hpp"
#include <cstring>
#include <cstdio>

namespace ubx
{

constexpr std::uint8_t port_configuration_class_id{0x06};
constexpr std::uint8_t port_configuration_message_id{0x00};

class port_configuration_message final : public message_base<port_configuration_message>
{
public:
    port_configuration_message() = default;

    template<typename read_iterator>
    port_configuration_message(const read_iterator &begin, const read_iterator &end);

    port_id get_port_id() const noexcept;

    const tx_ready_configuration& get_tx_ready_configuration() const noexcept;

    const uart_configuration& get_uart_configuration() const noexcept;

    const protocol_in_mask& get_protocol_in_mask() const noexcept;

    std::uint32_t get_baud_rate() const noexcept;

    const protocol_out_mask& get_protocol_out_mask() const noexcept;

    const port_flags& get_port_flags() const noexcept;

private:
    port_id m_port_id{port_id::uart0};
    tx_ready_configuration m_tx_ready_cfg;
    uart_configuration m_uart_cfg;
    protocol_in_mask m_protocol_in_mask;
    std::uint32_t m_baud_rate{0};
    protocol_out_mask m_protocol_out_mask;
    port_flags m_port_flags;
};

template<typename read_iterator>
port_configuration_message::port_configuration_message(const read_iterator &begin, const read_iterator &end)
{
    static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    constexpr std::uint8_t payload_length = 20;
    if(std::distance(begin, end) < payload_length)
    {
        return;
    }

    m_port_id = static_cast<port_id>(begin[0]);

    auto tx_ready_cfg_raw = utilities::get_uint16(begin[3], begin[2]);
    std::memcpy(&m_tx_ready_cfg, &tx_ready_cfg_raw, sizeof(tx_ready_configuration));

    auto uart_cfg_raw = utilities::get_uint32(begin[7], begin[6], begin[5], begin[4]);
    std::memcpy(&m_uart_cfg, &uart_cfg_raw, sizeof(uart_configuration));

    m_baud_rate = utilities::get_uint32(begin[11], begin[10], begin[9], begin[8]);

    auto proto_in_mask_raw = utilities::get_uint16(begin[13], begin[12]);
    std::memcpy(&m_protocol_in_mask, &proto_in_mask_raw, sizeof(protocol_in_mask));

    auto proto_out_mask_raw = utilities::get_uint16(begin[15], begin[14]);
    std::memcpy(&m_protocol_out_mask, &proto_out_mask_raw, sizeof(protocol_out_mask));

    auto port_flags_raw = utilities::get_uint16(begin[17], begin[16]);
    std::memcpy(&m_port_flags, &port_flags_raw, sizeof(port_flags));

    m_status = true;
}

inline port_id port_configuration_message::get_port_id() const noexcept
{
    return m_port_id;
}

inline const tx_ready_configuration &port_configuration_message::get_tx_ready_configuration() const noexcept
{
    return m_tx_ready_cfg;
}

inline const uart_configuration &port_configuration_message::get_uart_configuration() const noexcept
{
    return m_uart_cfg;
}

inline const protocol_in_mask &port_configuration_message::get_protocol_in_mask() const noexcept
{
    return m_protocol_in_mask;
}

inline uint32_t port_configuration_message::get_baud_rate() const noexcept
{
    return m_baud_rate;
}

inline const protocol_out_mask &port_configuration_message::get_protocol_out_mask() const noexcept
{
    return m_protocol_out_mask;
}

inline const port_flags &port_configuration_message::get_port_flags() const noexcept
{
    return m_port_flags;
}

} // namespace ubx

#endif // UBX_UART_PORT_CONFIGURATION_MESSAGE_HPP

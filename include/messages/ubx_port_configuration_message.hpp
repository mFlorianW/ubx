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
#include <array>

namespace ubx
{

constexpr std::uint8_t port_configuration_class_id{0x06};
constexpr std::uint8_t port_configuration_message_id{0x00};
constexpr std::uint8_t port_configuration_message_length{0x14};
constexpr std::uint8_t port_configuration_poll_message_length{0x01};

class port_configuration_message final : public message_base<port_configuration_message>
{
public:
    /**
     * Default consturcted port_configuration_message
     */
    port_configuration_message() = default;

    /**
     * Constructs the port_configuration_message from the given message buffer. After construction
     * the message can be validated is_valid() if the deserialization was successful.
     *
     * @param begin Start of the message buffer.
     * @param end End of the message buffer.
     */
    template<typename read_iterator>
    port_configuration_message(const read_iterator &begin, const read_iterator &end);

    /**
     * @return Gives the port id.
     */
    port_id get_port_id() const noexcept;

    /**
     * Set the port in the configuration.
     * @param id The id of the port.
     */
    void set_port_id(port_id id);

    /**
     * @return Gives the tx_ready_configuration.
     */
    const tx_ready_configuration& get_tx_ready_configuration() const noexcept;

    /**
     * Sets a tx_ready_configuration.
     * @param ready_cfg The new tx_ready_configuration.
     */
    void set_tx_ready_configuration(const tx_ready_configuration &tx_ready_cfg);

    /**
     * @return Gives the tx_uart_configuration.
     */
    const uart_configuration& get_uart_configuration() const noexcept;

    /**
     * Set a uart_configuration
     * @param uart_cfg The new uart configuration.
     */
    void set_uart_configuration(const uart_configuration &uart_cfg);

    /**
     * @return Gives the protocol_in_mask.
     */
    const protocol_in_mask& get_protocol_in_mask() const noexcept;

    /**
     * Sets a new protocol in mask.
     * @param proto_in_mask The protocol in mask.
     */
    void set_protocol_in_mask(const protocol_in_mask &proto_in_mask);

    /**
     * @return Gives the baud_rate.
     */
    std::uint32_t get_baud_rate() const noexcept;

    /**
     * Sets a new baud rate configuration.
     * @param baudrate The new baud rate
     */
    void set_baud_rate(std::uint32_t baudrate);

    /**
     * @return Gives the protocol_out_mask.
     */
    const protocol_out_mask& get_protocol_out_mask() const noexcept;

    /**
     * Set a new protocol out mask.
     * @param proto_out_mask The new protocol out mask
     */
    void set_protocol_out_mask(const protocol_out_mask &proto_out_mask);

    /**
     * @return Gives the port_flags.
     */
    const port_flags& get_port_flags() const noexcept;

    /**
     * Set new port flags configuration.
     * @param prt_flags New port flags configuration.
     */
    void set_port_flags(const port_flags &prt_flags);

    /**
     * Serialize the message into the given buffer with begin and end. The buffer must have the
     * at least the size of the port_configuration_message.
     * @param begin The begin of the buffer.
     * @param end The end of the buffer.
     * @return true serialization succesful otherwise false.
     */
    template<typename write_iterator>
    bool serialize(write_iterator begin, write_iterator end);

    template<typename write_iterator>
    bool serialize_poll_message(write_iterator begin, write_iterator end);

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

inline void port_configuration_message::set_port_id(port_id id)
{
    m_port_id = id;
}

inline const tx_ready_configuration &port_configuration_message::get_tx_ready_configuration() const noexcept
{
    return m_tx_ready_cfg;
}

inline void port_configuration_message::set_tx_ready_configuration(const tx_ready_configuration &tx_ready_cfg)
{
    m_tx_ready_cfg = tx_ready_cfg;
}

inline const uart_configuration &port_configuration_message::get_uart_configuration() const noexcept
{
    return m_uart_cfg;
}

inline void port_configuration_message::set_uart_configuration(const uart_configuration &uart_cfg)
{
    m_uart_cfg = uart_cfg;
}

inline const protocol_in_mask &port_configuration_message::get_protocol_in_mask() const noexcept
{
    return m_protocol_in_mask;
}

inline void port_configuration_message::set_protocol_in_mask(const protocol_in_mask &proto_in_mask)
{
    m_protocol_in_mask = proto_in_mask;
}

inline uint32_t port_configuration_message::get_baud_rate() const noexcept
{
    return m_baud_rate;
}

inline void port_configuration_message::set_baud_rate(uint32_t baudrate)
{
    m_baud_rate = baudrate;
}

inline const protocol_out_mask &port_configuration_message::get_protocol_out_mask() const noexcept
{
    return m_protocol_out_mask;
}

inline void port_configuration_message::set_protocol_out_mask(const protocol_out_mask &proto_out_mask)
{
    m_protocol_out_mask = proto_out_mask;
}

inline const port_flags &port_configuration_message::get_port_flags() const noexcept
{
    return m_port_flags;
}

inline void port_configuration_message::set_port_flags(const port_flags &prt_flags)
{
    m_port_flags = prt_flags;
}

template<typename write_iterator>
bool port_configuration_message::serialize(write_iterator begin, write_iterator end)
{
    static_assert(std::is_same<typename std::iterator_traits<write_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    //set port id
    begin[0] = static_cast<std::uint8_t>(m_port_id);

    //set resevered byte to 0
    begin[1] = 0;

    //serialize tx_ready_cfg
    auto raw_tx_ready_cfg = std::array<std::uint8_t, 2>{0};
    std::memcpy(&raw_tx_ready_cfg, &m_tx_ready_cfg, sizeof(tx_ready_configuration));
    begin[2] = raw_tx_ready_cfg[0];
    begin[3] = raw_tx_ready_cfg[1];

    //serialize uart configuration
    auto raw_uart_cfg = std::array<std::uint8_t, 4>{0};
    std::memcpy(&raw_uart_cfg, &m_uart_cfg, sizeof(uart_configuration));
    begin[4] = raw_uart_cfg[0];
    begin[5] = raw_uart_cfg[1];
    begin[6] = raw_uart_cfg[2];
    begin[7] = raw_uart_cfg[3];

    //serialize baud rate
    auto raw_baud_rate = std::array<std::uint8_t, 4>{0};
    std::memcpy(&raw_baud_rate, &m_baud_rate, sizeof(std::uint32_t));
    begin[8] = raw_baud_rate[0];
    begin[9] = raw_baud_rate[1];
    begin[10] = raw_baud_rate[2];
    begin[11] = raw_baud_rate[3];

    //serialize proto in mask
    auto raw_proto_in_mask = std::array<std::uint8_t, 2>{};
    std::memcpy(&raw_proto_in_mask, &m_protocol_in_mask, sizeof(protocol_out_mask));
    begin[12] = raw_proto_in_mask[0];
    begin[13] = raw_proto_in_mask[1];

    //serialize proto out mask
    auto raw_proto_out_mask = std::array<std::uint8_t, 2>{};
    std::memcpy(&raw_proto_out_mask, &m_protocol_out_mask, sizeof(protocol_out_mask));
    begin[14] = raw_proto_out_mask[0];
    begin[15] = raw_proto_out_mask[1];

    //serialize port flags
    auto raw_port_flags = std::array<std::uint8_t, 2>{};
    std::memcpy(&raw_port_flags, &m_port_flags, sizeof(port_flags));
    begin[16] = raw_port_flags[0];
    begin[17] = raw_port_flags[1];

    return true;
}

template<typename write_iterator>
inline bool port_configuration_message::serialize_poll_message(write_iterator begin, write_iterator end)
{
    static_assert(std::is_same<typename std::iterator_traits<write_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if(std::distance(begin, end) < port_configuration_poll_message_length)
    {
        return false;
    }

    begin[0] = static_cast<std::uint8_t>(m_port_id);
    return true;
}

} // namespace ubx

#endif // UBX_UART_PORT_CONFIGURATION_MESSAGE_HPP

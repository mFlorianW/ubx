#ifndef UBX_ACK_NACK_MESSAGE_HPP
#define UBX_ACK_NACK_MESSAGE_HPP

#include "private/ubx_ack_nack_message_reader.hpp"
#include "ubx_message.hpp"

namespace ubx
{

class ack_nack_message : public message_base<ack_nack_message>
{
public:
    /**
     * Class ID
     */
    constexpr static std::uint8_t ack_nack_class_id{0x05};

    /**
     * Message ID
     */
    constexpr static std::uint8_t ack_nack_message_id{0x00};

    /**
     * Message length
     */
    constexpr static std::uint8_t ack_nack_length{0x02};

    ack_nack_message() = default;

    template <typename read_iterator>
    ack_nack_message(const read_iterator &begin, const read_iterator &end);

    std::uint8_t get_not_acknowledged_class_id() const noexcept;

    std::uint8_t get_not_acknowledged_message_id() const noexcept;

private:
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

template <typename read_iterator>
ack_nack_message::ack_nack_message(const read_iterator &begin, const read_iterator &end)
    : message_base<ack_nack_message>()
{
    auto message_reader = ubx_ack_nack_message_reader();
    if (!message_reader.read(begin, end))
    {
        return;
    }

    m_class_id = message_reader.get_class_id();
    m_message_id = message_reader.get_message_id();
    m_status = true;
}

inline std::uint8_t ack_nack_message::get_not_acknowledged_class_id() const noexcept
{
    return m_class_id;
}

inline std::uint8_t ack_nack_message::get_not_acknowledged_message_id() const noexcept
{
    return m_message_id;
}

} // namespace ubx

#endif // UBX_ACK_NACK_MESSAGE_HPP

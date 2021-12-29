#ifndef UBX_ACK_MESSAGE_HPP
#define UBX_ACK_MESSAGE_HPP

#include "ubx_message.hpp"
#include "private/ubx_ack_nack_message_reader.hpp"
#include <iterator>

namespace ubx
{
class ack_message final : public message_base<ack_message>
{
public:
    ack_message() = default;

    template<typename read_iterator>
    ack_message(const read_iterator &begin, const read_iterator &end);

    std::uint8_t get_acknowledged_class_id() const noexcept;

    std::uint8_t get_acknowledged_message_id() const noexcept;

private:
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

template<typename read_iterator>
ack_message::ack_message(const read_iterator &begin, const read_iterator &end)
    : message_base<ack_message>()
{
    auto message_reader = ubx_ack_nack_message_reader();
    if(!message_reader.read(begin, end))
    {
        return;
    }

    m_class_id = message_reader.get_class_id();
    m_message_id = message_reader.get_message_id();
    m_status = true;
}

inline std::uint8_t ack_message::get_acknowledged_class_id() const noexcept
{
    return m_class_id;
}

inline std::uint8_t ack_message::get_acknowledged_message_id() const noexcept
{
    return m_message_id;
}

} // namespace ubx


#endif // UBX_ACK_MESSAGE_HPP

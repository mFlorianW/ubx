#ifndef UBX_NACK_MESSAGE_HPP
#define UBX_NACK_MESSAGE_HPP

#include "ubx_message.hpp"
#include "private/ubx_ack_nack_message_reader.hpp"

namespace ubx
{

class nack_message : public message_base<nack_message>
{
public:
    nack_message() = default;

    template<typename read_iterator>
    nack_message(const read_iterator &begin, const read_iterator &end);

    std::uint8_t get_not_acknowledged_class_id() const noexcept;

    std::uint8_t get_not_acknowledged_message_id() const noexcept;

private:
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

template<typename read_iterator>
nack_message::nack_message(const read_iterator &begin, const read_iterator &end)
    : message_base<nack_message>()
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

std::uint8_t nack_message::get_not_acknowledged_class_id() const noexcept
{
    return m_class_id;
}

inline std::uint8_t nack_message::get_not_acknowledged_message_id() const noexcept
{
    return m_message_id;
}

} // namespace ubx

#endif // UBX_NACK_MESSAGE_HPP

#ifndef UBX_ACK_MESSAGE_HPP
#define UBX_ACK_MESSAGE_HPP

#include "ubx_message.hpp"
#include "ubx_ack_nack_message.hpp"
#include <iterator>

namespace ubx
{
class ack_message final : public message_base<ack_message>, public ubx_ack_nack_message
{
public:
    ack_message() = default;

    template<typename read_iterator>
    ack_message(const read_iterator &begin, const read_iterator &end)
        : message_base<ack_message>()
        , ubx_ack_nack_message(begin, end)
    {
        if(m_succesful_parsed)
        {
            m_status = true;
        }
    }

    std::uint8_t get_acknowledged_class_id() const noexcept
    {
        return m_class_id;
    }

    std::uint8_t get_acknowledged_message_id() const noexcept
    {
        return m_message_id;
    }
};

} // namespace ubx


#endif // UBX_ACK_MESSAGE_HPP

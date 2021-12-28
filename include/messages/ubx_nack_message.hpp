#ifndef UBX_NACK_MESSAGE_HPP
#define UBX_NACK_MESSAGE_HPP

#include "ubx_message.hpp"
#include "ubx_ack_nack_message.hpp"

namespace ubx
{

class nack_message : public message_base<nack_message>, public ubx_ack_nack_message
{
public:
    nack_message() = default;

    template<typename read_iterator>
    nack_message(const read_iterator &begin, const read_iterator &end)
        : message_base<nack_message>()
        , ubx_ack_nack_message(begin, end)
    {
        if(m_succesful_parsed)
        {
            m_status = true;
        }
    }

    std::uint8_t get_not_acknowledged_class_id() const noexcept
    {
        return m_class_id;
    }

    std::uint8_t get_not_acknowledged_message_id() const noexcept
    {
        return m_message_id;
    }
};

};

#endif // UBX_NACK_MESSAGE_HPP

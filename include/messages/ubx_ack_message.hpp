#ifndef UBX_ACK_MESSAGE_HPP
#define UBX_ACK_MESSAGE_HPP

#include "ubx_message.hpp"
#include <iterator>

namespace ubx
{
class ack_message final : public message_base<ack_message>
{
public:
    ack_message() = default;

    template<typename read_iterator>
    ack_message(const read_iterator &begin, const read_iterator &end)
    {
        static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type,  std::uint8_t>::value,
                      "The iterator must be of type std::unit8_t");

        constexpr size_t msg_size = 2;
        if(std::distance(begin, end) < msg_size)
        {
            return;
        }

        m_class_id = begin[0];
        m_message_id = begin[1];

        m_status = true;
    }

    std::uint8_t get_acknowledged_class_id() const noexcept
    {
        return m_class_id;
    }

    std::uint8_t get_acknowledged_message_id() const noexcept
    {
        return m_message_id;
    }

private:
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

} // namespace ubx


#endif // UBX_ACK_MESSAGE_HPP

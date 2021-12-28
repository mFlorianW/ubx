#ifndef UBX_ACK_NACK_MESSAGE_HPP
#define UBX_ACK_NACK_MESSAGE_HPP

#include <iterator>

namespace ubx
{
class ubx_ack_nack_message
{
public:
    virtual ~ubx_ack_nack_message() = default;

protected:
    ubx_ack_nack_message() = default;

    template<typename read_iterator>
    ubx_ack_nack_message(const read_iterator &begin, const read_iterator &end)
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
        m_succesful_parsed = true;
    }

protected:
    bool m_succesful_parsed{false};
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

} //namespace ubx

#endif // UBX_ACK_NACK_MESSAGE_HPP

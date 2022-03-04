#ifndef UBX_ACK_NACK_MESSAGE_READER_HPP
#define UBX_ACK_NACK_MESSAGE_READER_HPP

#include <cstdint>
#include <iterator>

namespace ubx
{

class ubx_ack_nack_message_reader
{
public:
    ubx_ack_nack_message_reader() = default;

    template<typename read_iterator>
    bool read(const read_iterator &begin, const read_iterator &end);

    std::uint8_t get_class_id() const;

    std::uint8_t get_message_id() const;

private:
    std::uint8_t m_class_id{0};
    std::uint8_t m_message_id{0};
};

template<typename read_iterator>
bool ubx_ack_nack_message_reader::read(const read_iterator &begin, const read_iterator &end)
{
    static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type, std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    constexpr size_t msg_size = 2;
    if (std::distance(begin, end) < msg_size)
    {
        return false;
    }

    m_class_id = begin[0];
    m_message_id = begin[1];

    return true;
}

inline std::uint8_t ubx_ack_nack_message_reader::get_class_id() const
{
    return m_class_id;
}

inline std::uint8_t ubx_ack_nack_message_reader::get_message_id() const
{
    return m_message_id;
}

} // namespace ubx

#endif // UBX_ACK_NACK_MESSAGE_READER_HPP

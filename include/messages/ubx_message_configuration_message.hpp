#ifndef UBX_MESSAGE_CONFIGURATION_MESSAGE_HPP
#define UBX_MESSAGE_CONFIGURATION_MESSAGE_HPP

#include "ubx_message.hpp"
#include "ubx_types.hpp"
#include <array>

namespace ubx
{

constexpr std::uint8_t message_configuration_class_id{0x06};
constexpr std::uint8_t message_configuration_message_id{0x01};
constexpr std::uint8_t message_configuration_message_length{3};

class message_configuration final : public message_base<message_configuration>
{
public:
    /**
     * Creates an empty message configuration object.
     */
    message_configuration() = default;

    /**
     * Constructs a message configuration object from the given payload started at begin and ends at end.
     * @param begin payload begin
     * @param end payload end
     */
    template<typename read_iterator>
    message_configuration(const read_iterator &begin, const read_iterator &end);

    /**
     * @return Gives the class id.
     */
    class_id get_class_id() const noexcept;

    /**
     * Sets a new class id.
     * @param id The new class id.
     */
    void set_class_id(class_id id);

    /**
     * @return Gives the message id.
     */
    std::uint8_t get_message_id() const noexcept;

    /**
     * Set a new message id.
     * @param message_id The new message id.
     */
    void set_message_id(std::uint8_t message_id);

    /**
     * @return Gives the rate for the message.
     */
    std::uint8_t get_rate() const noexcept;

    /**
     * Sets a new rate.
     * @param rate The new rate.
     */
    void set_rate(std::uint8_t rate);

    /**
     * Serialize the message configuration in the given buffer from begin, to end.
     * @param begin The begin of the buffer.
     * @param end The end of the buffer.
     * @return True serialization is succesful, false buffer is to small.
     */
    template<typename write_iterator>
    bool serialize(write_iterator begin, write_iterator end);

private:
    class_id m_class_id{class_id::unknown};
    std::uint8_t m_message_id{0};
    std::uint8_t m_rate{0};
};

template<typename read_iterator>
message_configuration::message_configuration(const read_iterator &begin, const read_iterator &end)
{
    static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if(std::distance(begin, end) < message_configuration_message_length)
    {
        return;
    }

    m_class_id = static_cast<class_id>(begin[0]);
    m_message_id = begin[1];
    m_rate = begin[2];

    m_status = true;
}

inline class_id message_configuration::get_class_id() const noexcept
{
    return m_class_id;
}

inline void message_configuration::set_class_id(class_id id)
{
    m_class_id = id;
}

inline uint8_t message_configuration::get_message_id() const noexcept
{
    return m_message_id;
}

inline void message_configuration::set_message_id(uint8_t message_id)
{
    m_message_id = message_id;
}

inline uint8_t message_configuration::get_rate() const noexcept
{
    return m_rate;
}

inline void message_configuration::set_rate(uint8_t rate)
{
    m_rate = rate;
}

template<typename write_iterator>
bool message_configuration::serialize(write_iterator begin, write_iterator end)
{
    static_assert(std::is_same<typename std::iterator_traits<write_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if(std::distance(begin, end) < message_configuration_message_length)
    {
        return false;
    }

    begin[0] = static_cast<std::uint8_t>(m_class_id);
    begin[1] = m_message_id;
    begin[2] = m_rate;

    return true;
}

} //namespace ubx

#endif // UBX_MESSAGE_CONFIGURATION_MESSAGE_HPP
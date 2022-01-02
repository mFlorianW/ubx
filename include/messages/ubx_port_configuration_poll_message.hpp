#ifndef UBX_PORT_CONFIGURATION_POLL_MESSAGE_HPP
#define UBX_PORT_CONFIGURATION_POLL_MESSAGE_HPP

#include "ubx_types.hpp"
#include <cstdint>
#include <iterator>

namespace ubx
{

constexpr std::uint8_t port_configuration_poll_class_id{0x06};
constexpr std::uint8_t port_configuration_poll_message_id{0x00};

class port_configuration_poll_message
{
public:
    port_configuration_poll_message(port_id id = port_id::uart0);

    template<typename write_iterator>
    bool serialize(write_iterator begin, write_iterator end);
private:
    port_id m_port_id = port_id::uart1;
};

port_configuration_poll_message::port_configuration_poll_message(port_id id)
    : m_port_id(id)
{
}

template<typename write_iterator>
bool port_configuration_poll_message::serialize(write_iterator begin, write_iterator end)
{
    static_assert(std::is_same<typename std::iterator_traits<write_iterator>::value_type,  std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if(std::distance(begin, end) < 1)
    {
        return false;
    }

    begin[0] = static_cast<std::uint8_t>(m_port_id);
    return true;
}

} // namespace

#endif // UBX_PORT_CONFIGURATION_POLL_MESSAGE_HPP

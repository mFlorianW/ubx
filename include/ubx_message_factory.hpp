#ifndef UBX_MESSAGE_FACTORY_HPP
#define UBX_MESSAGE_FACTORY_HPP

#include "ubx_message.hpp"
#include <memory>

namespace ubx
{

class message_factory
{
public:
    template<typename  read_iterator>
    std::unique_ptr<message> create_message(std::uint8_t class_id,
                                            std::uint8_t message_id,
                                            read_iterator payload_begin,
                                            read_iterator payload_end);
};

} //namespace ubx

#endif // UBX_MESSAGE_FACTORY_HPP

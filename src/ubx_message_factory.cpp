#include "ubx_message_factory.hpp"

namespace ubx
{

template<typename read_iterator>
std::unique_ptr<message> message_factory::create_message(uint8_t class_id,
                                                         uint8_t message_id,
                                                         read_iterator payload_begin,
                                                         read_iterator payload_end)
{
    return nullptr;
}

}

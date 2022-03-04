#ifndef UBX_MESSAGE_DISPATCHER_HPP
#define UBX_MESSAGE_DISPATCHER_HPP

#include "ubx_cfg_prt_message.hpp"
#include "ubx_message.hpp"
#include <memory>

namespace ubx
{

class message_dispatcher
{
public:
    template<typename msg_handler_t, typename read_iterator>
    bool create_and_dispatch_message(msg_handler_t handler,
                                     std::uint8_t class_id,
                                     std::uint8_t message_id,
                                     read_iterator payload_begin,
                                     read_iterator payload_end)
    {
        if (class_id == cfg_prt_message::cfg_prt_message_class_id &&
            message_id == cfg_prt_message::cfg_port_message_message_id)
        {
            auto msg = cfg_prt_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            msg.dispatch(handler);
            return true;
        }

        return false;
    }
};

} // namespace ubx

#endif // UBX_MESSAGE_FACTORY_HPP

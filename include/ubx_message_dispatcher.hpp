#ifndef UBX_MESSAGE_DISPATCHER_HPP
#define UBX_MESSAGE_DISPATCHER_HPP

#include "ubx_ack_ack_message.hpp"
#include "ubx_ack_nack_message.hpp"
#include "ubx_cfg_msg_message.hpp"
#include "ubx_cfg_prt_message.hpp"
#include "ubx_cfg_rate_message.hpp"
#include "ubx_message.hpp"
#include "ubx_nav_pvt_message.hpp"
#include <memory>

namespace ubx
{

class message_dispatcher
{
public:
    template<typename msg_handler_t, typename read_iterator>
    bool create_and_dispatch_message(msg_handler_t &handler,
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

            handler.handle(msg);
            return true;
        }
        else if (class_id == ack_ack_message::ack_ack_class_id && message_id == ack_ack_message::ack_ack_message_id)
        {
            auto msg = ack_ack_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            handler.handle(msg);
            return true;
        }
        else if (class_id == nav_pvt_message::nav_pvt_class_id && message_id == nav_pvt_message::nav_pvt_message_id)
        {
            auto msg = nav_pvt_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            handler.handle(msg);
            return true;
        }
        else if (class_id == ack_nack_message::ack_nack_class_id && message_id == ack_nack_message::ack_nack_message_id)
        {
            auto msg = ack_nack_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            handler.handle(msg);
            return true;
        }
        else if (class_id == cfg_msg_message::cfg_msg_message_class_id &&
                 message_id == cfg_msg_message::cfg_msg_message_message_id)
        {
            auto msg = cfg_msg_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            handler.handle(msg);
            return true;
        }
        else if (class_id == cfg_rate_message::class_id && message_id == cfg_rate_message::message_id)
        {
            auto msg = cfg_rate_message(payload_begin, payload_end);
            if (msg.is_valid() == false)
            {
                return false;
            }

            handler.handle(msg);
            return true;
        }

        return false;
    }
};

} // namespace ubx

#endif // UBX_MESSAGE_FACTORY_HPP

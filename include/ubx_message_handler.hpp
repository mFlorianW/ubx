#ifndef UBX_MESSAGE_HANDLER_HPP
#define UBX_MESSAGE_HANDLER_HPP

#include "ubx_ack_ack_message.hpp"
#include "ubx_ack_nack_message.hpp"
#include "ubx_cfg_msg_message.hpp"
#include "ubx_cfg_prt_message.hpp"
#include "ubx_cfg_rate_message.hpp"
#include "ubx_nav_pvt_message.hpp"

namespace ubx
{

class message_handler
{
public:
    virtual ~message_handler() = default;

    virtual void handle(message&)
    {
    }

    virtual void handle(ack_ack_message&)
    {
    }

    virtual void handle(ack_nack_message&)
    {
    }

    virtual void handle(cfg_msg_message&)
    {
    }

    virtual void handle(cfg_prt_message&)
    {
    }

    virtual void handle(nav_pvt_message&)
    {
    }

    virtual void handle(cfg_rate_message&)
    {
    }
};

} // namespace ubx
#endif // UBX_MESSAGE_HANDLER_HPP

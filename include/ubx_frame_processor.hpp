#ifndef FRAME_PROCESSOR_H
#define FRAME_PROCESSOR_H

#include "ubx_frame.hpp"
#include "ubx_message_handler.hpp"
#include <algorithm>
#include <tuple>

namespace ubx
{

template<typename message_dispatcher_t, typename message_handler_t = message_handler>
class frame_processor
{
public:
    /**
     * Constructs a frame_processor
     * @param msg_factory The factory to create to create the messages from.
     * @param handler The handler which shall be called when a message is received.
     */
    frame_processor(message_dispatcher_t &msg_dispatcher, message_handler_t &handler)
        : m_msg_dispatcher(msg_dispatcher)
        , m_msg_handler(handler)
    {
    }

    virtual ~frame_processor() = default;

    template<typename read_iterator>
    void process_data(read_iterator data_begin, read_iterator data_end)
    {
        frame<read_iterator> fr;
        while (data_begin != data_end)
        {
            if (fr.read(data_begin, data_end) == frame_read_result::ok)
            {
                auto dispatched = m_msg_dispatcher.create_and_dispatch_message(m_msg_handler,
                                                                               fr.get_class_id(),
                                                                               fr.get_message_id(),
                                                                               fr.get_payload_begin(),
                                                                               fr.get_payload_end());

                // The message couldn't be created and dispatched
                if (!dispatched)
                {
                    ++data_begin;
                    continue;
                }

                data_begin = fr.get_frame_end();
            }
            else
            {
                ++data_begin;
            }
        }
    }

private:
    message_dispatcher_t &m_msg_dispatcher;
    message_handler_t &m_msg_handler;
};

} // namespace ubx

#endif // FRAME_PROCESSOR_H

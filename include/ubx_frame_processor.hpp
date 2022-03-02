#ifndef FRAME_PROCESSOR_H
#define FRAME_PROCESSOR_H

#include "ubx_frame.hpp"
#include <tuple>
#include <algorithm>

namespace ubx
{

template<typename message_factory_t, typename message_handler_t>
class frame_processor
{
public:
    /**
     * Constructs a frame_processor
     * @param msg_factory The factory to create to create the messages from.
     * @param handler The handler which shall be called when a message is received.
     */
    frame_processor(message_factory_t &msg_factory, message_handler_t &handler)
        : m_msg_factory(msg_factory)
        , m_msg_handler(handler)
    {
    }

    virtual ~frame_processor() = default;

    template<typename read_iterator>
    void process_data(read_iterator data_begin, read_iterator data_end)
    {
        frame<read_iterator> fr;
        while(data_begin != data_end)
        {
            if(fr.read(data_begin, data_end) == frame_read_result::ok)
            {
                auto msg_ptr = m_msg_factory.create_message(fr.get_class_id(),
                                                            fr.get_message_id(),
                                                            fr.get_payload_begin(),
                                                            fr.get_payload_end());
                msg_ptr->dispatch(m_msg_handler);
                data_begin = fr.get_frame_end();
            }
            else
            {
                ++data_begin;
            }
        }
    }

private:
    message_factory_t &m_msg_factory;
    message_handler_t &m_msg_handler;
};

} //namespace ubx

#endif // FRAME_PROCESSOR_H

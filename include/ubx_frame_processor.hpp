// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef FRAME_PROCESSOR_H
#define FRAME_PROCESSOR_H

#include "ubx_frame.hpp"
#include "ubx_message_dispatcher.hpp"
#include "ubx_message_handler.hpp"
#include <algorithm>
#include <tuple>

namespace ubx
{

template<typename message_handler_t = message_handler, typename message_dispatcher_t = message_dispatcher>
class frame_processor
{
public:
    /**
     * Constructs a frame_processor
     * @param handler The handler which shall be called when a message is received.
     * @param msg_dispatcher The factory to create the messages and dispatches to the handler.
     */
    frame_processor(message_handler_t& handler, message_dispatcher_t msg_dispatcher = message_dispatcher())
        : m_msg_dispatcher(msg_dispatcher)
        , m_msg_handler(handler)
    {
    }

    virtual ~frame_processor() = default;

    template<typename read_iterator>
    void process_data(read_iterator data_begin, read_iterator data_end)
    {
        auto incomingBufferSize = std::distance(data_begin, data_end);
        auto freeElementsInBuffer = sInternalBufferSize - mWriteIndex;
        // Buffer is nearly full, reset it and contains only garbage.
        if (freeElementsInBuffer < incomingBufferSize) {
            mReadIndex = 0;
            mWriteIndex = 0;
        }

        // copy incoming data to internal buffer
        std::copy(data_begin, data_end, mIncomeBuffer.begin() + mWriteIndex);
        mWriteIndex += incomingBufferSize;

        frame<std::array<std::uint8_t, sInternalBufferSize>::iterator> fr;
        while (mReadIndex < mWriteIndex) {
            auto result = fr.read(mIncomeBuffer.begin() + mReadIndex, mIncomeBuffer.end());
            if (result == frame_read_result::ok) {
                auto dispatched = m_msg_dispatcher.create_and_dispatch_message(m_msg_handler,
                                                                               fr.get_class_id(),
                                                                               fr.get_message_id(),
                                                                               fr.get_payload_begin(),
                                                                               fr.get_payload_end());
                // The message couldn't be created and dispatched
                if (!dispatched) {
                    ++mReadIndex;
                    continue;
                }

                mReadIndex += std::distance(mIncomeBuffer.begin() + mReadIndex, fr.get_frame_end());
            } else if (result == frame_read_result::incomplete_data) {
                break;
            } else {
                ++mReadIndex;
            }
        }

        // We computed all data in incoming buffer.
        if (mReadIndex == mWriteIndex) {
            mReadIndex = 0;
        }
    }

private:
    static constexpr std::size_t sInternalBufferSize{300};
    std::array<std::uint8_t, sInternalBufferSize> mIncomeBuffer;
    std::size_t mWriteIndex{0};
    std::size_t mReadIndex{0};
    message_dispatcher_t m_msg_dispatcher;
    message_handler_t& m_msg_handler;

    static_assert(std::is_copy_constructible<message_dispatcher_t>(), "Message dispatcher must be copyable");
    static_assert(std::is_copy_assignable<message_dispatcher_t>(), "Message dispatcher must be copyable");
};

} // namespace ubx

#endif // FRAME_PROCESSOR_H

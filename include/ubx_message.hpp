#ifndef UBXMESSAGE_HPP
#define UBXMESSAGE_HPP

#include <iostream>
#include <type_traits>
#include <typeinfo>

namespace ubx
{
class message
{
public:
    /**
     * Default base destructor
     */
    virtual ~message() = default;

    /**
     * Gives the status about the message if it is in a valid state.
     * The status is set by a message after deserializing a message from the raw data.
     * If the message is setup manually the is valid status will be always false.
     *
     * @return True the message was deserialized correctly, otherwise false.
     */
    bool is_valid() const noexcept
    {
        return m_status;
    }

protected:
    bool m_status{false};
};

template<typename message_t>
class message_base : public message
{
public:
    /**
     * Dispatch the message to the given handler.
     * @param handler The that shall handle the message.
     */
    template<typename handler_t>
    void dispatch(handler_t &handler)
    {
        handler.handle(static_cast<message_t &>(*this));
    }
};

} // namespace ubx
#endif // UBXMESSAGE_HPP

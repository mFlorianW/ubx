#ifndef UBXMESSAGE_HPP
#define UBXMESSAGE_HPP

namespace ubx
{
/**
 * Base class for every ubx related message.
 */
template<class message_t>
class message
{
public:
    /**
     * Default virtual destructor
     */
    virtual ~message() = default;

    /**
     * Dispatch the message to the handler.
     *
     * @param handler The handler that shall receive the message.
     */
    template<typename handler_t>
    void dispatch(handler_t &handler)
    {
        handler.handle(static_cast<message_t&>(*this));
    }

protected:
    /**
     * Constructs a message.
     */
    message() = default;
};

} //namespace ubx
#endif // UBXMESSAGE_HPP

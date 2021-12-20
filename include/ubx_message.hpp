#ifndef UBXMESSAGE_HPP
#define UBXMESSAGE_HPP

namespace ubx
{
template<typename handler_t>
class message
{
public:
    ~message() = default;

    void handle(handler_t &handler)
    {
        dispatch_impl(handler);
    }

protected:
    virtual void dispatch_impl(handler_t& handler) = 0;
//    {
//        handler.handle(static_cast<message&>(*this));
//    }
};

/**
 * Base class for every ubx related message.
 */
template<typename message_t, typename handler_t>
class message_base : public message<handler_t>
{
protected:
    /**
     * Call the message specific handle function in the handler.
     *
     * @param handler The handler that shall receive the message.
     */
    void dispatch_impl(handler_t &handler) override
    {
        handler.handle(static_cast<message_t&>(*this));
    }
};

} //namespace ubx
#endif // UBXMESSAGE_HPP

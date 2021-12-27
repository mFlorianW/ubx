#ifndef UBXMESSAGE_HPP
#define UBXMESSAGE_HPP

#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace ubx
{
class message_handler_base
{
public:
    virtual ~message_handler_base() = default;
};

template<typename message_type>
class message_handler : public message_handler_base
{
public:
    virtual ~message_handler() = default;

    virtual void handle(message_type &message) = 0;
};

class message
{
public:
    virtual ~message() = default;

    virtual void dispatch(message_handler_base &handler) = 0;

protected:
    template<typename message_type>
    void dispatch_impl(message_handler_base &handler, message_type &message)
    {
        static_cast<message_handler<message_type>&>(handler).handle(message);
    }
};

template<typename message_t>
class message_base : public message
{
public:
    void dispatch(message_handler_base &handler) override
    {
        dispatch_impl(handler, *this);
    }
};

} //namespace ubx
#endif // UBXMESSAGE_HPP

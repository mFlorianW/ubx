#define CATCH_CONFIG_MAIN
#include "ubx_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

class testable_message : public message_base<testable_message>
{
};

class testable_message2 : public message_base<testable_message2>
{
};

class test_message_handler
{
public:
    void handle(testable_message2 &msg)
    {
        handle_called2 = true;
    }

    void handle(testable_message &msg)
    {
        handle_called = true;
    }

    bool handle_called{false};
    bool handle_called2{false};
};

TEST_CASE("Dispatch shall call handle object")
{
    testable_message msg;
    testable_message2 msg2;
    test_message_handler hdl;

    msg.dispatch(hdl);
    msg2.dispatch(hdl);

    REQUIRE(hdl.handle_called == true);
    REQUIRE(hdl.handle_called2 == true);
}

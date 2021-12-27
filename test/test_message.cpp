#define CATCH_CONFIG_MAIN
#include "ubx_message.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

class testable_message;
class test_message_handler : public message_handler<testable_message>
{
public:
    void handle(testable_message& msg)
    {
        handle_called = true;
    }

    bool handle_called{false};
};

class testable_message : public message_base<testable_message>
{
};

TEST_CASE("Dispatch shall call handle object")
{
    testable_message msg;
    test_message_handler hdl;

    msg.dispatch(hdl);

    REQUIRE(hdl.handle_called == true);
}

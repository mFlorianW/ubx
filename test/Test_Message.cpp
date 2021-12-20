#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "UbxMessage.hpp"

using namespace ubx;

class testable_message : public message<testable_message>
{
};

class testable_handler
{
public:
    void handle(testable_message& msg)
    {
        handle_called = true;
    }

    bool handle_called{false};
};

TEST_CASE("Dispatch shall call handle object")
{
    testable_message msg;
    testable_handler hdl;

    msg.dispatch(hdl);

    REQUIRE(hdl.handle_called == true);
}

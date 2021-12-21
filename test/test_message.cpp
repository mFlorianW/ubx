#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "ubx_message.hpp"

using namespace ubx;

class testable_message;
class testing_handler
{
public:
    void handle(message<testing_handler> &msg)
    {
    }

    void handle(testable_message& msg)
    {
        handle_called = true;
    }

    bool handle_called{false};
};

class testable_message : public message_base<testable_message, testing_handler>
{
};

TEST_CASE("Dispatch shall call handle object")
{
    testable_message msg;
    testing_handler hdl;

    msg.handle(hdl);

    REQUIRE(hdl.handle_called == true);
}

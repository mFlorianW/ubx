#define CATCH_CONFIG_MAIN
#include "ubx_message_dispatcher.hpp"
#include "ubx_message_handler.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

class testing_message_hander : public message_handler
{
public:
    void handle(ack_ack_message &msg) override
    {
    }
};

TEST_CASE("Compile test only to check if it is possible to override functions of message handler")
{
    testing_message_hander handler;
    message_dispatcher dispatcher;
    std::array<std::uint8_t, 0> emptyFrame;

    dispatcher.create_and_dispatch_message(static_cast<message_handler &>(handler),
                                           0x0,
                                           0x02,
                                           emptyFrame.cbegin(),
                                           emptyFrame.cend());
}

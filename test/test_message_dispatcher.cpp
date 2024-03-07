#define CATCH_CONFIG_MAIN
#include "test_raw_messages.hpp"
#include "ubx_message_dispatcher.hpp"
#include "ubx_message_handler.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

class testing_message_hander : public message_handler
{
public:
    void handle(ack_ack_message& msg) override
    {
        handleAckIsCalled = true;
    }

    bool handleAckIsCalled{false};
};

TEST_CASE("Checks if it is possible to override functions of message handler and they got called")
{
    testing_message_hander handler;
    message_dispatcher dispatcher;

    dispatcher.create_and_dispatch_message(static_cast<message_handler&>(handler),
                                           ack_ack_message::ack_ack_class_id,
                                           ack_ack_message::ack_ack_message_id,
                                           valid_ack_msg.cbegin(),
                                           valid_ack_msg.cend());

    REQUIRE(handler.handleAckIsCalled == true);
}

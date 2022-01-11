#define CATCH_CONFIG_MAIN
#include "ubx_cfg_msg_message.hpp"
#include "test_raw_messages.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

TEST_CASE("The message configuration shall give the class id from  valid parsed data")
{
    auto msg_cfg = cfg_msg_message(valid_message_configuration.begin(), valid_message_configuration.end());
    auto class_id = msg_cfg.get_class_id();
    REQUIRE(class_id == class_id::sec);
}

TEST_CASE("The message configuration shall give the message id from parsed data")
{
    auto msg_cfg = cfg_msg_message(valid_message_configuration.begin(), valid_message_configuration.end());
    auto message_id = msg_cfg.get_message_id();
    REQUIRE(message_id == 0x20);
}

TEST_CASE("The message configuration shall give the message rate from parsed data")
{
    auto msg_cfg = cfg_msg_message(valid_message_configuration.begin(), valid_message_configuration.end());
    auto rate = msg_cfg.get_rate();
    REQUIRE(rate == 0x05);
}

TEST_CASE("The message configuration shall be  valid after read in payload data")
{
    auto msg_cfg = cfg_msg_message(valid_message_configuration.begin(), valid_message_configuration.end());
    REQUIRE(msg_cfg.is_valid() == true);
}

TEST_CASE("The message configuration shall be invalid after read in broken payload data")
{
    auto msg_cfg = cfg_msg_message(invalid_message_configuration.begin(), invalid_message_configuration.end());
    REQUIRE(msg_cfg.is_valid() == false);
}

TEST_CASE("The message configuration shall serialize the set class id.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    msg_cfg.set_class_id(class_id::sec);
    msg_cfg.serialize(msg_buffer.begin(), msg_buffer.end());
    REQUIRE(msg_buffer[0] == valid_message_configuration[0]);
}

TEST_CASE("The message configuration shall serialize the set message id.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    msg_cfg.set_message_id(0x20);
    msg_cfg.serialize(msg_buffer.begin(), msg_buffer.end());
    REQUIRE(msg_buffer[1] == valid_message_configuration[1]);
}

TEST_CASE("The message configuration shall serialize the set rate.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    msg_cfg.set_rate(0x05);
    msg_cfg.serialize(msg_buffer.begin(), msg_buffer.end());
    REQUIRE(msg_buffer[2] == valid_message_configuration[2]);
}

TEST_CASE("The message configuration shall return true when successful serialized")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    REQUIRE(msg_cfg.serialize(msg_buffer.begin(), msg_buffer.end()) == true);
}

TEST_CASE("The message configuration serialize shall return false when buffer is to small")
{
    auto msg_buffer = std::array<std::uint8_t, 2>{0};
    auto msg_cfg = cfg_msg_message{};
    REQUIRE(msg_cfg.serialize(msg_buffer.begin(), msg_buffer.end()) == false);
}

TEST_CASE("The message configuration shall be able to serialize the class id into a poll request.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_poll_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    msg_cfg.set_class_id(class_id::sec);
    msg_cfg.serialize_poll_message(msg_buffer.begin(), msg_buffer.end());
    REQUIRE(msg_buffer[0] == valid_message_configuration_poll[0]);
}

TEST_CASE("The message configuration shall be able to serialize the message id into a poll request.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_poll_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    msg_cfg.set_message_id(0x20);
    msg_cfg.serialize_poll_message(msg_buffer.begin(), msg_buffer.end());
    REQUIRE(msg_buffer[1] == valid_message_configuration_poll[1]);
}

TEST_CASE("The message configuration poll serialization shall return on success.")
{
    auto msg_buffer = std::array<std::uint8_t, cfg_msg_poll_message_length>{0};
    auto msg_cfg = cfg_msg_message{};
    REQUIRE(msg_cfg.serialize_poll_message(msg_buffer.begin(), msg_buffer.end()) == true);
}

TEST_CASE("The message configuration poll serialization shall return false when the buffer is to small.")
{
    auto msg_buffer = std::array<std::uint8_t, 1>{0};
    auto msg_cfg = cfg_msg_message{};
    REQUIRE(msg_cfg.serialize_poll_message(msg_buffer.begin(), msg_buffer.end()) == false);
}


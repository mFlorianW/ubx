#define CATCH_CONFIG_MAIN
#include "ubx_frame_factory.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

namespace
{
constexpr auto expected_frame_buffer = std::array<std::uint8_t, 9>{0xb5, 0x62, 0x20, 0x10, 0x01, 0x00, 0x20, 0x51, 0x03};
constexpr auto payload_begin = expected_frame_buffer.cbegin() + 6;
constexpr auto payload_end = expected_frame_buffer.cbegin() + 7;
}

TEST_CASE("Frame factory shall put ubx preamble in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x00,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[0] == '['); //catch interprets frame_buffer[0] as '['
    REQUIRE(frame_buffer[1] == expected_frame_buffer[1]);
}

TEST_CASE("Frame factory shall put class id in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x00,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[2] == expected_frame_buffer[2] );
}

TEST_CASE("Frame factory shall put message id in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x10,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[3] == expected_frame_buffer[3]);
}

TEST_CASE("Frame factory shall put payload length in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x10,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[4] == expected_frame_buffer[4]);
    REQUIRE(frame_buffer[5] == expected_frame_buffer[5]);
}

TEST_CASE("Frame factory shall put payload in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x10,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[6] == expected_frame_buffer[6]);
}

TEST_CASE("Frame factory shall put checksum in frame buffer")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    frame_factory::create_frame(0x20,
                                0x10,
                                payload_begin,
                                payload_end,
                                frame_buffer.begin(),
                                frame_buffer.end());

    REQUIRE(frame_buffer[7] == expected_frame_buffer[7]);
    REQUIRE(frame_buffer[8] == expected_frame_buffer[8]);
}

TEST_CASE("Frame factory shall return true when frame correctly build")
{
    auto frame_buffer = std::array<std::uint8_t, 9>{0};

    REQUIRE(frame_factory::create_frame(0x20,
                                        0x10,
                                        payload_begin,
                                        payload_end,
                                        frame_buffer.begin(),
                                        frame_buffer.end()) == true);
}

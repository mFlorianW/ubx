#define CATCH_CONFIG_MAIN
#include "ubx_frame.hpp"
#include <catch2/catch.hpp>

using namespace ubx;

namespace
{
auto frame_without_payload = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x00, 0x00, 0x00};
auto frame_with_payload = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
auto frame_with_crc_error = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x00, 0x00};
auto frame_chunk = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00};
auto frame_corrupted = std::vector<std::uint8_t>{0xB5, 0x61, 0x01, 0x22, 0x01, 0x00};
} // namespace

using vector_frame = frame<std::vector<std::uint8_t>::const_iterator>;

TEST_CASE("Get class id from frame.")
{
    vector_frame fr;
    fr.read(frame_without_payload.cbegin(), frame_with_payload.cend());

    REQUIRE(fr.get_class_id() == class_id::nav);
}

TEST_CASE("Get message id from frame")
{
    vector_frame fr;
    fr.read(frame_without_payload.cbegin(), frame_with_payload.cend());

    REQUIRE(fr.get_message_id() == 0x22);
}

TEST_CASE("Get payload length from frame")
{
    vector_frame fr;
    fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());

    REQUIRE(fr.get_payload_length() == 0x01);
}

TEST_CASE("Check frame checksum")
{
    vector_frame fr;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(result == frame_read_result::ok);
}

TEST_CASE("Get error when checkusm not match")
{
    vector_frame fr;

    auto result = fr.read(frame_with_crc_error.cbegin(), frame_with_crc_error.cend());
    REQUIRE(result == frame_read_result::checksum_error);
}

TEST_CASE("Give ok status on succesful read frame")
{
    vector_frame fr;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(result == frame_read_result::ok);
}

TEST_CASE("Give not enough data on reading frame chunk")
{
    vector_frame fr;

    auto result = fr.read(frame_chunk.cbegin(), frame_chunk.cend());
    REQUIRE(result == frame_read_result::incomplete_data);
}

TEST_CASE("Detect corrupted data broken preamble")
{
    vector_frame fr;

    auto result = fr.read(frame_corrupted.cbegin(), frame_chunk.cend());
    REQUIRE(result == frame_read_result::corrupted_frame);
}

TEST_CASE("Return read iterator for payload begin")
{
    vector_frame fr;
    const auto expected_iterator = frame_with_payload.cbegin() + 6;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(result == frame_read_result::ok);
    REQUIRE(fr.get_payload_begin() == expected_iterator);
}

TEST_CASE("Return end iterator for the payload")
{
    vector_frame fr;
    const auto expected_iterator = frame_with_payload.cbegin() + 7;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(result == frame_read_result::ok);
    REQUIRE(fr.get_payload_end() == expected_iterator);
}

TEST_CASE("Return end iterator for the frame")
{
    vector_frame fr;
    const auto expected_iterator = frame_with_payload.cbegin() + 9;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.cend());
    REQUIRE(result == frame_read_result::ok);
    REQUIRE(fr.get_frame_end() == expected_iterator);
}

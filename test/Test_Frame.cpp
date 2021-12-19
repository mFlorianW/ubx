#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "UbxFrame.hpp"

using namespace Ubx;

namespace
{
auto frame_without_payload =  std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x00, 0x00, 0x00};
auto frame_with_payload =  std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x44, 0xB0};
auto frame_with_crc_error =  std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00, 0x20, 0x00, 0x00};
auto frame_chunk = std::vector<std::uint8_t>{0xB5, 0x62, 0x01, 0x22, 0x01, 0x00};
auto frame_corrupted = std::vector<std::uint8_t>{0xB5, 0x61, 0x01, 0x22, 0x01, 0x00};
}

using vector_frame = frame<std::vector<std::uint8_t>::const_iterator>;

TEST_CASE("Get class id from frame.")
{
    vector_frame fr;
    fr.read(frame_without_payload.cbegin(), frame_without_payload.size());

    REQUIRE(fr.get_class_id() == class_id::nav);
}

TEST_CASE("Get message id from frame")
{
    vector_frame fr;
    fr.read(frame_without_payload.cbegin(), frame_without_payload.size());

    REQUIRE(fr.get_message_id() == 0x22);
}

TEST_CASE("Get payload length from frame")
{
    vector_frame fr;
    fr.read(frame_with_payload.cbegin(), frame_with_payload.size());

    REQUIRE(fr.get_payload_length() == 0x01);
}

TEST_CASE("Check frame checksum")
{
    vector_frame fr;

    fr.read(frame_with_payload.cbegin(), frame_with_payload.size());
    REQUIRE(fr.validate_checksum() == true);
}

TEST_CASE("Get error when checkusm not match")
{
    vector_frame fr;

    fr.read(frame_with_crc_error.cbegin(), frame_with_crc_error.size());
    REQUIRE(fr.validate_checksum() == false);
}

TEST_CASE("Give ok status on succesful read frame")
{
    vector_frame fr;

    auto result = fr.read(frame_with_payload.cbegin(), frame_with_payload.size());
    REQUIRE(result == vector_frame::read_result::ok);
}

TEST_CASE("Give not enough data on reading frame chung")
{
    vector_frame fr;

    auto result = fr.read(frame_chunk.cbegin(), frame_chunk.size());
    REQUIRE(result == vector_frame::read_result::incomplete_data);
}

TEST_CASE("Dected corrupted data broken preamble")
{
    vector_frame fr;

    auto result = fr.read(frame_corrupted.cbegin(), frame_chunk.size());
    REQUIRE(result == vector_frame::read_result::corrupted_frame);
}

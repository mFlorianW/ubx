#ifndef __FRAME__H__
#define __FRAME__H__

#include "ubx_types.hpp"
#include "ubx_utilities.hpp"
#include <iterator>

namespace ubx
{

enum class frame_read_result
{
    ok,
    incomplete_data,
    corrupted_frame,
    checksum_error
};

/**
 * Representation of a UBX frame.
 *
 * @code{.cpp}
 * // Create an instance of the class as follow when raw data is stored in vector.
 * using vector_frame = frame<std::vector<std::uint8_t>::const_iterator>;
 * vector_frame fr;
 * fr.read(raw_data.cbegin());
 * ...
 * @endcode
 */
template<class read_iterator>
class frame
{
public:
    /**
     * @return class_id The class id of the frame.
     */
    class_id get_class_id() const noexcept
    {
        return m_class_id;
    }

    /**
     * @return The message id of the frame.
     */
    std::uint8_t get_message_id() const noexcept
    {
        return m_message_id;
    }

    /**
     * @return The length of the playload.
     */
    std::uint16_t get_payload_length() const noexcept
    {
        return m_payload_length;
    }

    /**
     * @return True when the checkums is correct otherwise false;
     */
    bool validate_checksum() const noexcept
    {
        return m_checksum_result;
    }

    /**
     * Reads the frame from the iterator with given length.
     *
     * @param frame_begin iterator to the begin of the frame
     * @param length the length of the buffer
     *
     * @return frame_read_result::incomplete_data when the frame isn't received completly.
     * @return frame_read_result::corrupted_data when the frame contains corrupted data.
     * @return frame_read_result::ok frame succesful read.
     */
    frame_read_result read(read_iterator const& frame_begin, read_iterator const& frame_end)
    {
        static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type, std::uint8_t>::value,
                      "The iterator must be of type std::unit8_t");

        constexpr size_t frame_header_size = 6;
        constexpr size_t frame_crc_length = 2;
        auto len = std::distance(frame_begin, frame_end);
        if (len < frame_header_size) {
            return frame_read_result::incomplete_data;
        }

        // Check for preamble
        if (frame_begin[0] != 0xb5 || frame_begin[1] != 0x62) {
            return frame_read_result::corrupted_frame;
        }

        m_class_id = static_cast<class_id>(frame_begin[2]);
        m_message_id = frame_begin[3];
        m_payload_length = utilities::convert_2byte_to_int<std::uint16_t>(frame_begin[5], frame_begin[4]);

        constexpr size_t checksum_length = 2;
        if (len < frame_header_size + m_payload_length + checksum_length) {
            return frame_read_result::incomplete_data;
        }

        if (calculate_checksum(frame_begin, len) != frame_read_result::ok) {
            return frame_read_result::checksum_error;
        }

        m_payload_begin = frame_begin + frame_header_size;
        m_payload_end = frame_begin + frame_header_size + m_payload_length;
        m_frame_end = frame_begin + frame_header_size + m_payload_length + frame_crc_length;
        return frame_read_result::ok;
    }

    /**
     * @note Is only valid after read(...) results with frame_read_result::ok.
     * @return Gives the iterator where the payload starts.
     */
    read_iterator const& get_payload_begin() const noexcept
    {
        return m_payload_begin;
    }

    /**
     * @note Is only valid after read(...) results with frame_read_result::ok.
     * @return Gives the iterator where the payload ends.
     */
    read_iterator const& get_payload_end() const noexcept
    {
        return m_payload_end;
    }

    read_iterator const& get_frame_end() const noexcept
    {
        return m_frame_end;
    }

private:
    frame_read_result calculate_checksum(read_iterator const& raw_frame, size_t len)
    {
        std::uint8_t received_cka = raw_frame[6 + m_payload_length];
        std::uint8_t received_ckb = raw_frame[7 + m_payload_length];

        // class, message id and payload
        constexpr size_t constant_frame_data = 4;
        auto length_of_checksum_data = m_payload_length + constant_frame_data;
        auto checksum = utilities::calculate_checksum(raw_frame + 2, length_of_checksum_data);

        if (checksum.ck_a != received_cka || checksum.ck_b != received_ckb) {
            return frame_read_result::checksum_error;
        }

        return frame_read_result::ok;
    }

private:
    class_id m_class_id = class_id::unknown;
    std::uint8_t m_message_id{0};
    std::uint16_t m_payload_length{0};
    bool m_checksum_result{false};
    read_iterator m_payload_begin;
    read_iterator m_payload_end;
    read_iterator m_frame_end;
};

} // namespace ubx

#endif //!__FRAME__H__

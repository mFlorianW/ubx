#ifndef __FRAME__H__
#define __FRAME__H__

#include "UbxTypes.hpp"
#include "UbxUtilities.hpp"
#include <vector>
#include <iterator>

namespace Ubx
{
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
    enum class read_result
    {
        ok,
        incomplete_data,
        corrupted_frame
    };

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
     * @param data pointer to the buffer
     * @param length the length of the buffer
     * @return incomplete_data when the frame isn't received completly.
     * @return corrupted_data when the frame contains corrupted data.
     * return ok frame succesful read.
     */
    read_result read(read_iterator raw_frame, size_t len)
    {
        static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type,  std::uint8_t>::value,
                      "The iterator must be of type std::unit8_t");

        if(len < 5)
        {
            return read_result::incomplete_data;
        }

        //Check for preamble
        if(raw_frame[0] != 0xb5 || raw_frame[1] != 0x62)
        {
            return read_result::corrupted_frame;
        }

        m_class_id = static_cast<class_id>(raw_frame[2]);
        m_message_id = raw_frame[3];
        m_payload_length = Utilities::get_uint16(raw_frame[5], raw_frame[4]);

        if(len < 6 + m_payload_length)
        {
            return read_result::incomplete_data;
        }

        calculate_checksum(raw_frame, len);
        return read_result::ok;
    }

private:
    void calculate_checksum(read_iterator raw_frame, size_t len)
    {
        std::uint16_t cka = 0;
        std::uint16_t ckb = 0;
        std::uint8_t received_cka = raw_frame[6+m_payload_length];
        std::uint8_t received_ckb = raw_frame[7+m_payload_length];

        // class, message id and payload
        constexpr size_t constant_frame_data = 4;
        auto length_of_checksum_data = m_payload_length + constant_frame_data;
        for(size_t i = 0; i < length_of_checksum_data;  ++i)
        {
            cka = cka + raw_frame[2 + i];
            ckb = ckb + cka;
        }

        cka = cka & 0xFF;
        ckb = ckb & 0xFF;

        if(cka == received_cka && ckb == received_ckb)
        {
            m_checksum_result = true;
        }
    }

private:
    class_id m_class_id = class_id::unknown;
    std::uint8_t m_message_id{0};
    std::uint16_t m_payload_length{0};
    bool m_checksum_result{false};
};

} //Ubx


#endif  //!__FRAME__H__

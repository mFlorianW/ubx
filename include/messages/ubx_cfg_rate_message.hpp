// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBX_CFG_RATE_MESSAGE_HPP
#define UBX_CFG_RATE_MESSAGE_HPP

#include "ubx_message.hpp"
#include "ubx_utilities.hpp"
#include <array>
#include <cstring>

namespace ubx
{

enum class time_ref
{
    utc = 0,
    gps = 1,
    glonass = 2,
    beidou = 3,
    galileo = 4,
    navlc = 0,
};

class cfg_rate_message : public message
{
public:
    /**
     * The class id of the UBX-CFG-RATE message
     */
    static constexpr std::uint8_t class_id = 0x06;

    /**
     * The message id of the UBX-CFG-RATE message
     */
    static constexpr std::uint8_t message_id = 0x08;

    /**
     * The length of the UBX-CFG-RATE message
     */
    static constexpr std::uint8_t message_length = 0x06;

    /**
     * Default constructor
     */
    cfg_rate_message() = default;

    /**
     * Constructs the UBX-CFG-RATE from the given message buffer. After construction
     * the message can be validated is_valid() if the deserialization was successful.
     *
     * @param begin Start of the message buffer.
     * @param end End of the message buffer.
     */
    template<typename read_iterator>
    cfg_rate_message(read_iterator const& begin, read_iterator const& end);

    /**
     * @return Gives the meas rate in ms.
     */
    std::uint16_t get_meas_rate() const;

    /**
     * Sets a new meas rate value.
     * @param meas_rate The new meas rate value.
     */
    void set_meas_rate(std::uint16_t meas_rate);

    /**
     * @return Gives the nav rate cycles.
     */
    std::uint16_t get_nav_rate() const;

    /**
     * Sets a new nav rate value.
     * @param meas_rate The new nav rate value.
     */
    void set_nav_rate(std::uint16_t nav_rate);

    /**
     * @return Gives the time ref.
     */
    time_ref get_time_ref() const;

    /**
     * Sets a new time ref value.
     * @param meas_rate The new time ref value.
     */
    void set_time_ref(time_ref time_ref);

    /**
     * Serialize the message into the given buffer with begin and end. The buffer must have the
     * at least the size of the port_configuration_message.
     * @param begin The begin of the buffer.
     * @param end The end of the buffer.
     * @return true serialization succesful otherwise false.
     */
    template<typename write_iterator>
    bool serialize(write_iterator begin, write_iterator end);

private:
    std::uint16_t m_meas_rate{0};
    std::uint16_t m_nav_rate{0};
    time_ref m_time_ref{time_ref::utc};
};

template<typename read_iterator>
cfg_rate_message::cfg_rate_message(read_iterator const& begin, read_iterator const& end)
    : message()
{
    static_assert(std::is_same<typename std::iterator_traits<read_iterator>::value_type, std::uint8_t>::value,
                  "The iterator must be of type std::unit8_t");

    if (std::distance(begin, end) < message_length) {
        return;
    }

    m_meas_rate = utilities::convert_2byte_to_int<std::uint16_t>(begin[1], begin[0]);
    m_nav_rate = utilities::convert_2byte_to_int<std::uint16_t>(begin[3], begin[2]);
    m_time_ref = static_cast<time_ref>(utilities::convert_2byte_to_int<std::uint16_t>(begin[5], begin[4]));

    m_status = true;
}

inline uint16_t cfg_rate_message::get_meas_rate() const
{
    return m_meas_rate;
}

inline void cfg_rate_message::set_meas_rate(uint16_t meas_rate)
{
    m_meas_rate = meas_rate;
}

inline uint16_t cfg_rate_message::get_nav_rate() const
{
    return m_nav_rate;
}

inline void cfg_rate_message::set_nav_rate(uint16_t nav_rate)
{
    m_nav_rate = nav_rate;
}

inline time_ref cfg_rate_message::get_time_ref() const
{
    return m_time_ref;
}

inline void cfg_rate_message::set_time_ref(time_ref time_ref)
{
    m_time_ref = time_ref;
}

template<typename write_iterator>
bool cfg_rate_message::serialize(write_iterator begin, write_iterator end)
{
    if (std::distance(begin, end) < message_length) {
        return false;
    }

    auto raw_uint16_value = std::array<std::uint8_t, 2>{0};
    // serialize meas rate
    std::memcpy(&raw_uint16_value, &m_meas_rate, sizeof(std::uint16_t));
    begin[0] = raw_uint16_value[0];
    begin[1] = raw_uint16_value[1];

    // serialize nav rate
    std::memcpy(&raw_uint16_value, &m_nav_rate, sizeof(std::uint16_t));
    begin[2] = raw_uint16_value[0];
    begin[3] = raw_uint16_value[1];

    // serialize time ref
    std::uint16_t raw_time_ref = static_cast<std::uint16_t>(m_time_ref);
    std::memcpy(&raw_uint16_value, &raw_time_ref, sizeof(std::uint16_t));
    begin[4] = raw_uint16_value[0];
    begin[5] = raw_uint16_value[1];

    return true;
}

} // namespace ubx

#endif // UBX_CFG_RATE_MESSAGE_HPP

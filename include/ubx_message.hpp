// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifndef UBXMESSAGE_HPP
#define UBXMESSAGE_HPP

#include <iostream>
#include <type_traits>
#include <typeinfo>

namespace ubx
{

class message
{
public:
    /**
     * Default base destructor
     */
    virtual ~message() = default;

    /**
     * Gives the status about the message if it is in a valid state.
     * The status is set by a message after deserializing a message from the raw data.
     * If the message is setup manually the is valid status will be always false.
     *
     * @return True the message was deserialized correctly, otherwise false.
     */
    bool is_valid() const noexcept
    {
        return m_status;
    }

protected:
    bool m_status{false};
};

} // namespace ubx
#endif // UBXMESSAGE_HPP

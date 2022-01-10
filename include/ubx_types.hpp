#ifndef __UBXTYPES__H__
#define __UBXTYPES__H__

#include <cstdint>

namespace ubx
{

enum class_id : uint8_t
{
    unknown = 0x00,
    nav = 0x01,
    rxm = 0x02,
    inf = 0x04,
    ack = 0x05,
    cfg = 0x06,
    upd = 0x09,
    mon = 0x0A,
    aid = 0x0B,
    tim = 0x0D,
    esf = 0x10,
    mga = 0x13,
    log = 0x21,
    sec = 0x27,
    hnr = 0x28,
};

enum class port_id : std::uint8_t
{
    uart0 = 0x01,
    uart1 = 0x02
};

enum class psm_state : std::uint8_t
{
    not_active = 0,
    enabled = 1,
    acquisition = 2,
    tracking = 3,
    power_optimized_tracking = 4,
    inactive = 5,
};

enum class carrier_phase_range_solution_status
{
    no_solution = 0,
    with_floating_ambiguities = 1,
    with_fixed_ambiguities = 2,
};

} //ubx


#endif  //!__UBXTYPES__H__

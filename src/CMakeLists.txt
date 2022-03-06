add_library(UbxObject OBJECT)
add_library(Ubx::Object ALIAS UbxObject)

target_sources(UbxObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ubx_utilities.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_frame.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_frame_factory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_frame_processor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_message_dispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_message_handler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_ack_ack_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_ack_nack_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_cfg_msg_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_cfg_prt_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_nav_pvt_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/messages/ubx_cfg_rate_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/private/ubx_ack_nack_message_reader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_tx_ready_configuration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_fix_status_flags3.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_fix_status_flags2.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_uart_configuration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_port_flags.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_protocol_in_mask.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_validity_flags.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_fix_status_flags.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/types/ubx_protocol_out_mask.hpp
)

target_include_directories(UbxObject
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/messages>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/messages>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/types>
)

add_library(Ubx SHARED)
add_library(Ubx::Ubx ALIAS Ubx)

target_link_libraries(Ubx
    UbxObject
)

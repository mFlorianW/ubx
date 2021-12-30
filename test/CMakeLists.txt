find_package(Catch2 CONFIG REQUIRED)

include(CTest)
include(Catch)

add_executable(test_frame test_frame.cpp)
target_link_libraries(test_frame PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_message test_message.cpp)
target_link_libraries(test_message PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_frame_processor test_frame_processor.cpp)
target_link_libraries(test_frame_processor PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_ack_message test_ack_message.cpp)
target_link_libraries(test_ack_message PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_nack_message test_nack_message.cpp)
target_link_libraries(test_nack_message PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_port_configuration_poll_message test_port_configuration_poll_message.cpp)
target_link_libraries(test_port_configuration_poll_message PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_uart_port_configuration_message test_uart_port_configuration_message.cpp)
target_link_libraries(test_uart_port_configuration_message PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_uart_configuration test_uart_configuration.cpp)
target_link_libraries(test_uart_configuration PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_protocol_in_mask test_protocol_in_mask.cpp)
target_link_libraries(test_protocol_in_mask PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_protocol_out_mask test_protocol_out_mask.cpp)
target_link_libraries(test_protocol_out_mask PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_port_flags test_port_flags.cpp)
target_link_libraries(test_port_flags PRIVATE Catch2::Catch2 Ubx::Object)

catch_discover_tests(test_frame)
catch_discover_tests(test_message)
catch_discover_tests(test_frame_processor)
catch_discover_tests(test_ack_message)
catch_discover_tests(test_nack_message)
catch_discover_tests(test_uart_port_configuration_message)
catch_discover_tests(test_uart_configuration)
catch_discover_tests(test_protocol_in_mask)
catch_discover_tests(test_protocol_out_mask)
catch_discover_tests(test_port_flags)

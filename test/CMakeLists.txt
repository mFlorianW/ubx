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

catch_discover_tests(test_frame)
catch_discover_tests(test_message)
catch_discover_tests(test_frame_processor)
catch_discover_tests(test_ack_message)
catch_discover_tests(test_nack_message)

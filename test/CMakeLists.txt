find_package(Catch2 CONFIG REQUIRED)

enable_testing()

include(CTest)
include(Catch)

add_executable(test_frame Test_Frame.cpp)
target_link_libraries(test_frame PRIVATE Catch2::Catch2 Ubx::Object)

add_executable(test_message Test_Message.cpp)
target_link_libraries(test_message PRIVATE Catch2::Catch2 Ubx::Object)

catch_discover_tests(test_message)

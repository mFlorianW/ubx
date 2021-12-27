add_library(UbxObject OBJECT)
add_library(Ubx::Object ALIAS UbxObject)

target_sources(UbxObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ubx_utilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ubx_message_factory.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_frame.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_types.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_utilities.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_frame_processor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/ubx_message_factory.hpp
)

target_include_directories(UbxObject
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/messages>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/messages>
)

add_library(Ubx SHARED)
add_library(Ubx::Ubx ALIAS Ubx)

target_link_libraries(Ubx
    UbxObject
)

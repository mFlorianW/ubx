add_library(UbxObject OBJECT)
add_library(Ubx::Object ALIAS UbxObject)

target_sources(UbxObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ubx_utilities.cpp
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

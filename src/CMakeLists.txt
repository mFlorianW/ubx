add_library(UbxObject OBJECT)
add_library(Ubx::Object ALIAS UbxObject)

target_sources(UbxObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/UbxUtilities.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/UbxFrame.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/UbxTypes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/UbxUtilities.hpp
)

target_include_directories(UbxObject
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

add_library(Ubx SHARED)
add_library(Ubx::Ubx ALIAS Ubx)

target_link_libraries(Ubx
    UbxObject
)

file(GLOB SRC_FILES
    $ENV{UBX_SOLUTION_PATH}/src/*.cpp
)

idf_component_register(
SRCS
    "${SRC_FILES}"
INCLUDE_DIRS
    "$ENV{UBX_SOLUTION_PATH}/include"
    "$ENV{UBX_SOLUTION_PATH}/include/messages"
    "$ENV{UBX_SOLUTION_PATH}/include/types"
)

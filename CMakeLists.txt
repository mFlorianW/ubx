cmake_minimum_required(VERSION 3.5)

project(LibUBX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_CATCH2_FETCH "This option enables that catch2 is fetched in configuration" OFF)

################################################################################
# Modules
################################################################################
include(GenerateExportHeader)
include(FeatureSummary)

add_subdirectory(src)

if(ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TEST)

feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES PACKAGES_FOUND)

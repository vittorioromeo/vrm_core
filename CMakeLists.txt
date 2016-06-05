cmake_minimum_required(VERSION 3.0)

# Include `vrm_cmake`.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../vrm_cmake/cmake/"
    "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")

include(vrm_cmake)

# Basic project setup.
vrm_cmake_init_project(vrm_core)
vrm_cmake_find_extlib(vrm_pp)

# Alias the include directory.
set(VRM_CORE_INC_DIR "${VRM_CORE_SOURCE_DIR}/include/")
include_directories("${VRM_CORE_INC_DIR}")

# Other compiler flags.
vrm_cmake_add_common_compiler_flags()

# The `check` target runs all tests and examples.
vrm_check_target()

# Setup subdirectories.
add_subdirectory(test)

# Create header-only install target (automatically glob)
vrm_cmake_header_only_install_glob("${VRM_CORE_INC_DIR}" "include")

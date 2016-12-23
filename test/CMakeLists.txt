# Add a custom target for the unit tests.
add_custom_target(tests COMMENT "Build all the unit tests.")

# `check` depends on `tests`.
add_dependencies(check tests)

# Include directories.
include_directories(${VRM_CORE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Generate all the header unit tests.
# vrm_cmake_generate_public_header_tests_glob("*.hpp" "${VRM_CORE_SOURCE_DIR}/include")

# Generate all the unit tests.
vrm_cmake_generate_unit_tests_glob("*.cpp")

foreach(_x IN LISTS vrm_cmake_out)
#{
    target_compile_options(${_x} PUBLIC "-fdiagnostics-color=always")

    vrm_cmake_augment_test_asan(${_x})
    vrm_cmake_augment_test_ofast(${vrm_cmake_out})

    vrm_cmake_augment_test_tsan(${_x})
    vrm_cmake_augment_test_ofast(${vrm_cmake_out})

    vrm_cmake_augment_test_ubsan(${_x})
    vrm_cmake_augment_test_ofast(${vrm_cmake_out})
#}
endforeach()

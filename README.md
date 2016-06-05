# vrm_core [![Build Status](https://travis-ci.org/SuperV1234/vrm_core.svg?branch=master)](https://travis-ci.org/SuperV1234/vrm_core)

General-purpose C++14 utility library.

## Intended usage (quick start)

1. Add this repository, [SuperV1234/vrm_cmake](https://github.com/SuperV1234/vrm_cmake) and [SuperV1234/vrm_pp](https://github.com/SuperV1234/vrm_pp) as submodules of your project, as subfolders in `your_project/extlibs/`:

    ```bash
    git submodule add   https://github.com/SuperV1234/vrm_cmake.git   your_project/extlibs/vrm_cmake
    git submodule add   https://github.com/SuperV1234/vrm_pp.git      your_project/extlibs/vrm_pp
    git submodule add   https://github.com/SuperV1234/vrm_core.git    your_project/extlibs/vrm_core
    ```

2. Include `vrm_cmake` in your project's `CMakeLists.txt` and look for the `vrm_pp` and `vrm_core` extlibs:

    ```cmake
    # Include `vrm_cmake`:
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")
    include(vrm_cmake)

    # Find `vrm_pp` and `vrm_core`:
    vrm_cmake_find_extlib(vrm_pp)
    vrm_cmake_find_extlib(vrm_core)
    ```

*(Altenatively, only add `vrm_core` and `vrm_cmake` as submodules, and recursively pull submodules to let `vrm_core` find `vrm_pp`.)*
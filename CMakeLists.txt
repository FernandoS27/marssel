cmake_minimum_required(VERSION 3.6)

project(marssel C CXX)

# Determine if we're built as a subproject (using add_subdirectory)
# or if this is the master project.
set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
endif()

# options
option(MARSSEL_TESTS "Build tests" ${MASTER_PROJECT})
option(MARSSEL_WARNINGS_AS_ERRORS "Warnings as errors" ${MASTER_PROJECT})
option(MARSSEL_DEBUG_BUILD "Build for debug" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

include(CreateDirectoryGroups)

#
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# como minimo vamos a usar el estandard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WARN_DEPRECATED ON)

# Disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif()

# queremos que lo programacion sea extricta y no utilice comportamiento indefinido
if (MSVC)
    set(MARSSEL_CXX_FLAGS
        /W4
        /w34263 # Non-virtual member function hides base class virtual function
        /w44265 # Class has virtual functions, but destructor is not virtual
        /w34456 # Declaration of 'var' hides previous local declaration
        /w34457 # Declaration of 'var' hides function parameter
        /w34458 # Declaration of 'var' hides class member
        /w34459 # Declaration of 'var' hides global definition
        /w34946 # Reinterpret-cast between related types
        /wd4592 # Symbol will be dynamically initialized (implementation limitation)
        /permissive- # Stricter C++ standards conformance
        /MP
        /Zi
        /Zo
        /EHsc
        /Zc:throwingNew # Assumes new never returns null
        /Zc:inline # Omits inline functions from object-file output
        /DNOMINMAX)

    if (MARSSEL_WARNINGS_AS_ERRORS)
        list(APPEND MARSSEL_CXX_FLAGS
             /WX)
    endif()

    if (MARSSEL_DEBUG_BUILD)
        list(APPEND MARSSEL_CXX_FLAGS
            /Od)
    else()
        list(APPEND MARSSEL_CXX_FLAGS
            /O2)
    endif()

    if (CMAKE_VS_PLATFORM_TOOLSET MATCHES "LLVM-vs[0-9]+")
        list(APPEND MARSSEL_CXX_FLAGS
             -Qunused-arguments
             -Wno-missing-braces)
    endif()

else()
    set(MARSSEL_CXX_FLAGS
        -Wall
        -Wextra
        -Wcast-qual
        -pedantic
        -pedantic-errors
        -Wfatal-errors
        -Wno-missing-braces)

    if (MARSSEL_WARNINGS_AS_ERRORS)
        list(APPEND KEPLER3D_CXX_FLAGS
             -Werror)
    endif()

    if (MARSSEL_DEBUG_BUILD)
        list(APPEND KEPLER3D_CXX_FLAGS
            -O0 -g)
    else()
        list(APPEND MARSSEL_CXX_FLAGS
        -O2 -msse4)
    endif()


endif()

# Enable unit-testing.
enable_testing(true)

if (MARSSEL_TESTS)
  # add catch2 to the include list
  include_directories(externals/catch2)
endif()

# Marssel project files
add_subdirectory(src)
if (MARSSEL_TESTS)
    add_subdirectory(tests)
endif()

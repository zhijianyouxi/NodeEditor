# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.18)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

if (DEFINED ENV{VCPKG_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    message(STATUS "VCPKG_TRIPLET: $ENV{VCPKG_TRIPLET}")
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_TRIPLET}" CACHE STRING "")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(NodeEditor
        LANGUAGES CXX C
        DESCRIPTION "节点编辑器"
        HOMEPAGE_URL https://github.com/zhijianyouxi/NodeEditor
)
option(NODE_BUILD_EDITOR "Build node editor" ON)
option(NODE_BUILD_SHARED "Build shared library for NodeEditor" OFF)
option(NODE_DBG "Enable debug mode" OFF)
option(NODE_NO_WARNING "Use customized compiler warnings" OFF)

#if (NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()
set(CMAKE_BUILD_TYPE Debug)
message(STATUS "Build directory: ${PROJECT_BINARY_DIR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

cmake_path(GET CMAKE_CXX_COMPILER STEM LAST_ONLY ZENO_CXX_COMPILER_BINARY)
message(STATUS "Current C++ compiler is ${ZENO_CXX_COMPILER_BINARY} (${CMAKE_CXX_COMPILER})")

if (NODE_NO_WARNING)  # Use our customized warning flags
    set(NODE_OLD_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-all -Wno-cpp -Wno-deprecated-declarations -Wno-enum-compare -Wno-ignored-attributes -Wno-extra -Wreturn-type -Wmissing-declarations -Wnon-virtual-dtor -Wsuggest-override -Wconversion-null -Wuninitialized -Wno-format-security -Wnarrowing -Wno-maybe-uninitialized")
    endif()
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    endif()
endif()

macro (node_dbg_msvc project)
    if (WIN32)
        target_compile_options(${project} PRIVATE /Zi /O2 /Ob2)
        # Tell linker to include symbol data
        set_target_properties(${project} PROPERTIES
                LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF"
        )
        # Set file name & location
        set_target_properties(${project} PROPERTIES
                COMPILE_PDB_NAME ${project}
                COMPILE_PDB_OUTPUT_DIR ${project}
        )
    endif()
endmacro()

#target_compile_options($<$<COMPILE_LANGUAGE:CXX>: $<IF:$<CXX_COMPILER_ID:MSVC>, /utf-8 /EHa, >>)
add_compile_options("/utf-8")
add_compile_options("/EHa")
# 包含子项目。
add_subdirectory ("Nodes")

if (NODE_BUILD_EDITOR)
    message(STATUS "Building Editor")
    add_subdirectory ("UI")
endif()



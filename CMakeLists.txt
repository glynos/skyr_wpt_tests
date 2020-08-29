# Copyright (c) Glyn Matthews 2020.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)


cmake_minimum_required(VERSION 3.14)

project(
        skyr-url-wpt-tests
        VERSION 1.0.0
        HOMEPAGE_URL https://cpp-netlib.github.io/url
        DESCRIPTION "A C++ library that implements the WhatWG URL specification"
        LANGUAGES CXX
)

set(skyr_URL_TAG "main" CACHE STRING "The Git tag or branch for the URL repo under test")
set(skyr_WPT_TAG "merge_pr_23753" CACHE STRING "The Git tag or branch for the WPT test data" )

set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(tl-expected CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include(FetchContent)

message(STATUS "Fetching skyr-url")
set(skyr_WARNINGS_AS_ERRORS OFF)
set(skyr_BUILD_TESTS OFF)
set(skyr_BUILD_EXAMPLES OFF)
set(skyr_BUILD_DOCS OFF)
FetchContent_Declare(
        skyr-url
        GIT_REPOSITORY https://github.com/cpp-netlib/url
        GIT_TAG ${skyr_URL_TAG}
)

message(STATUS "Fetching platform test data")
FetchContent_Declare(
        wpt
        GIT_REPOSITORY https://github.com/web-platform-tests/wpt
        GIT_TAG ${skyr_WPT_TAG}
)

FetchContent_MakeAvailable(skyr-url wpt)

enable_testing()
add_subdirectory(tests)

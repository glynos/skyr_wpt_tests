# Copyright (c) Glyn Matthews 2020.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include(${skyr-url_SOURCE_DIR}/cmake/skyr-url-functions.cmake)

function(skyr_create_test file_name output_dir test_name)
    skyr_remove_extension(${file_name} test)
    add_executable(${test} ${test}.cpp)
    add_dependencies(${test} skyr::skyr-url)
    target_link_libraries(
            ${test}
            PRIVATE
            skyr::skyr-url
            Catch2::Catch2
            nlohmann_json::nlohmann_json
            fmt::fmt
    )
    set_target_properties(
            ${test}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${output_dir}
    )
    set(${test_name} ${test} PARENT_SCOPE)
endfunction()

foreach (
        file_name
        url_web_platform_tests.cpp
        url_wpt_setter_tests.cpp)
    skyr_create_test(${file_name} ${PROJECT_BINARY_DIR}/tests test)
    add_test(${test} ${PROJECT_BINARY_DIR}/tests/${test})
endforeach ()

file(GLOB WPT_TEST_DATA ${wpt_SOURCE_DIR}/url/resources/*.json)
file(COPY ${WPT_TEST_DATA} DESTINATION ${PROJECT_BINARY_DIR}/tests)

cmake_minimum_required(VERSION 3.18)

# add the executable
add_library(aoc
    stl.h
    aoc.h
)

target_include_directories(aoc PUBLIC .)

target_link_libraries(aoc
    PUBLIC
        boost
)

function(add_day aoc_day)
    set(test_target "test_day${aoc_day}")
    set(input_header "generated/input${aoc_day}.h")

    file(READ "test/example${aoc_day}.in" aoc_example_input)
    string(REPLACE "\n" "\\n\"\n    \"" aoc_example_input "${aoc_example_input}")
    
    file(READ "test/personal${aoc_day}.in" aoc_personal_input)
    string(REPLACE "\n" "\\n\"\n    \"" aoc_personal_input "${aoc_personal_input}")
    
    configure_file("test/template.h" "${input_header}")

    add_executable("${test_target}" "test/${test_target}.cpp" "${CMAKE_CURRENT_BINARY_DIR}/${input_header}")

    target_include_directories("${test_target}" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")

    target_link_libraries("${test_target}"
        PUBLIC
            aoc
            gtest
            gtest_main
    )

    add_test(NAME "${test_target}" COMMAND "${test_target}")
    
    target_sources(aoc PRIVATE "day${aoc_day}.cpp")
endfunction()

add_day(01)
add_day(02)
add_day(03)


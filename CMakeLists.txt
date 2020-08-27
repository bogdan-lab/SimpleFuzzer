cmake_minimum_required(VERSION 3.10)

project(SimpleFuzzer 
	LANGUAGES C)

add_executable(simple_fuzzer
                src/simple_fuzzer.c
                src/argument_handler.c)

target_compile_options(simple_fuzzer PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Wunused
                                        -Wconversion -Wsign-conversion
                                       -Warray-bounds -Wformat -Wimplicit -g)

target_include_directories(simple_fuzzer PRIVATE ${CMAKE_SOURCE_DIR}/include)


cmake_minimum_required(VERSION 3.10)

project(SimpleFuzzer 
	LANGUAGES C)

add_executable(simple_fuzzer
                src/simple_fuzzer.c)

target_compile_options(simple_fuzzer PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Wunused
                                        -Wconversion -Wsign-conversion
                                       -Warray-bounds -Wformat -Wimplicit)


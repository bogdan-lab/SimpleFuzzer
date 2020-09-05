cmake_minimum_required(VERSION 3.10)

project(SimpleFuzzer 
	LANGUAGES C)

add_library(utilities OBJECT
	src/utils.c
	)
target_include_directories(utilities PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_properties(utilities PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
#set(CMAKE_SHARED_LINKER_FLAGS "-Wl --export-all-symbols")

add_library(words_data_base SHARED 
	src/words.c
	$<TARGET_OBJECTS:utilities>
	)
target_include_directories(words_data_base PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(fuzz_generators STATIC
	src/generators.c
	$<TARGET_OBJECTS:utilities>
	)
target_include_directories(fuzz_generators PRIVATE ${CMAKE_SOURCE_DIR}/include)


add_executable(simple_fuzzer
                src/simple_fuzzer.c
                src/argument_handler.c
		$<TARGET_OBJECTS:utilities>
                )

target_compile_options(simple_fuzzer PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Wunused -Wincompatible-pointer-types
                                        -Wconversion -Wsign-conversion -Wimplicit-function-declaration
                                       -Warray-bounds -Wformat -Wimplicit -g)
target_include_directories(simple_fuzzer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(simple_fuzzer PRIVATE words_data_base)


if(SANITIZE)
	target_compile_options(simple_fuzzer PRIVATE -g -O0 -fsanitize=address)
	target_link_libraries(simple_fuzzer PRIVATE -lasan)
endif()

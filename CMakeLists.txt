cmake_minimum_required(VERSION 3.10)

project(SimpleFuzzer 
	LANGUAGES C)

add_library(utilities OBJECT
	src/utils.c
	)
target_include_directories(utilities PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_properties(utilities PROPERTIES POSITION_INDEPENDENT_CODE TRUE)


set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

#----------------------------------------------------------------------
add_library(words_data_base SHARED 
	src/words.c
	$<TARGET_OBJECTS:utilities>
	)
target_include_directories(words_data_base PRIVATE ${INCLUDE_DIRS})

install(TARGETS words_data_base 
	LIBRARY
	DESTINATION ${LIB_INSTALL_DIR}
	CONFIGURATIONS Release)
install(FILES include/words.h 
	DESTINATION ${LIB_INSTALL_DIR} 
	RENAME words_data_base.h)

#------------------------------------------------------------------------

add_library(fuzz_generators STATIC
	src/generators.c
	$<TARGET_OBJECTS:utilities>
	)
target_include_directories(fuzz_generators PRIVATE ${INCLUDE_DIRS})
install(TARGETS fuzz_generators
	ARCHIVE
	DESTINATION ${LIB_INSTALL_DIR}
	CONFIGURATIONS Release)
install(FILES include/generators.h
	DESTINATION ${LIB_INSTALL_DIR}
	RENAME fuzz_generators.h)

#------------------------------------------------------------------------
set(CMAKE_INSTALL_RPATH ${LIB_INSTALL_DIR})
add_executable(simple_fuzzer
                src/simple_fuzzer.c
                src/argument_handler.c
		$<TARGET_OBJECTS:utilities>
                )

target_compile_options(simple_fuzzer PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Wunused -Wincompatible-pointer-types
                                        -Wconversion -Wsign-conversion -Wimplicit-function-declaration
                                       -Warray-bounds -Wformat -Wimplicit)
target_include_directories(simple_fuzzer PRIVATE ${INCLUDE_DIRS})
target_link_libraries(simple_fuzzer PRIVATE words_data_base)

install(TARGETS simple_fuzzer
	RUNTIME
	DESTINATION ${BIN_INSTALL_DIR}
	CONFIGURATIONS Release)

#-----------------------------------------------------------------------

if(SANITIZE)
	target_compile_options(simple_fuzzer PRIVATE -g -O0 -fsanitize=address)
	target_link_libraries(simple_fuzzer PRIVATE -lasan)
endif()

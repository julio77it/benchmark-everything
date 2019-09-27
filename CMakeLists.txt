cmake_minimum_required(VERSION 3.13.4)
project(benchmark VERSION 1.0 LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(FATAL_ERROR "GCC version must be at least 9.0!")
endif()

set(CMAKE_CXX_STANDARD 17)

#
# CONAN DEPENDENCIES
#
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
            	  "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(BASIC_SETUP
		CONANFILE conanfile.txt
		CMAKE_TARGETS
		BUILD missing)

#
# Project Configuration
#
set(WARNING_FLAGS "-fconcepts -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2")
set(CMAKE_CXX_FLAGS "${WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")


#
# FATTORIALE
#
add_executable(factorial
	           src/factorial.cpp)

target_link_libraries(factorial
		              PUBLIC CONAN_PKG::fmt)

target_include_directories(factorial
		      	           PUBLIC CONAN_PKG::fmt)


add_executable(factorial_benchmark
	           src/factorial_benchmark.cpp)

target_link_libraries(factorial_benchmark
                        PUBLIC CONAN_PKG::google-benchmark
                        PUBLIC CONAN_PKG::fmt
                        PUBLIC CONAN_PKG::range-v3
                        PUBLIC CONAN_PKG::boost)

target_include_directories(factorial_benchmark
                            PUBLIC CONAN_PKG::google-benchmark
                            PUBLIC CONAN_PKG::fmt
                            PUBLIC CONAN_PKG::range-v3
                            PUBLIC CONAN_PKG::boost)

#
# EXECUTION POLICIES
#
add_executable(media_benchmark
	           src/media_benchmark.cpp)

target_link_libraries(media_benchmark
                        PUBLIC CONAN_PKG::TBB
                        PUBLIC CONAN_PKG::google-benchmark
                        PUBLIC CONAN_PKG::range-v3)

target_include_directories(media_benchmark
                            PUBLIC CONAN_PKG::google-benchmark
                            PUBLIC CONAN_PKG::range-v3)


#
# FIBONACCI
#
add_executable(fibonacci
	           src/fibonacci.cpp)

target_link_libraries(fibonacci
                      PUBLIC CONAN_PKG::fmt)

target_include_directories(fibonacci
                            PUBLIC CONAN_PKG::fmt)

add_executable(fibonacci_benchmark
	           src/fibonacci_benchmark.cpp)

target_link_libraries(fibonacci_benchmark
                      PUBLIC CONAN_PKG::google-benchmark
                      PUBLIC CONAN_PKG::fmt
                      PUBLIC CONAN_PKG::boost)

target_include_directories(fibonacci_benchmark
                            PUBLIC CONAN_PKG::google-benchmark
                            PUBLIC CONAN_PKG::fmt
                            PUBLIC CONAN_PKG::boost)

#
# STRING
#
add_executable(string_benchmark
                   src/string_benchmark.cpp)

target_link_libraries(string_benchmark
                      PUBLIC CONAN_PKG::google-benchmark
                      PUBLIC CONAN_PKG::fmt
                      PUBLIC CONAN_PKG::boost)

target_include_directories(string_benchmark
                            PUBLIC CONAN_PKG::google-benchmark
                            PUBLIC CONAN_PKG::fmt
                            PUBLIC CONAN_PKG::boost)

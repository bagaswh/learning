cmake_minimum_required(VERSION 3.10)
project(beejnetprog C)

set(CMAKE_C_STANDARD 11)

# Set output directory for binaries
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Print source directory for debugging
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Default to release build if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# AddressSanitizer configuration for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring AddressSanitizer for Debug build")
    # These flags need to be added to both compiler and linker
    set(ASAN_FLAGS "-static-libasan -fsanitize=address -fno-omit-frame-pointer")

    # Add the sanitizer flags to the compiler flags
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${ASAN_FLAGS}")

    # Add the sanitizer flags to the linker flags
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${ASAN_FLAGS}")
endif()

# Option to specify a single source file to compile
option(SINGLE_SOURCE "Compile only a specific source file" OFF)
set(SINGLE_SOURCE_FILE "" CACHE STRING "The specific source file to compile")

# Collect all C source files in addrinfo directory
file(GLOB ADDRINFO_SOURCES "${CMAKE_SOURCE_DIR}/addrinfo/*.c")
message(STATUS "Found source files: ${ADDRINFO_SOURCES}")

# If SINGLE_SOURCE is enabled, compile only that file
if(SINGLE_SOURCE AND SINGLE_SOURCE_FILE)
    list(FILTER ADDRINFO_SOURCES INCLUDE REGEX "${SINGLE_SOURCE_FILE}")
    if(NOT ADDRINFO_SOURCES)
        message(FATAL_ERROR "Specified file ${SINGLE_SOURCE_FILE} not found in addrinfo directory")
    endif()
endif()

# Loop through each source file and create an executable
foreach(SRC ${ADDRINFO_SOURCES})
    # Get the file name without extension
    get_filename_component(EXEC_NAME ${SRC} NAME_WE)

    # Create executable
    add_executable(${EXEC_NAME} ${SRC}
            addrinfo/dhcp_client.h
            addrinfo/slice.c
            addrinfo/slice.h)

    # Apply the correct compiler flags based on build type
    target_compile_options(${EXEC_NAME} PRIVATE
            $<$<CONFIG:Debug>:-g -Wall -Wextra>
            $<$<CONFIG:Release>:-O3 -Wall -Wextra>
    )
endforeach()

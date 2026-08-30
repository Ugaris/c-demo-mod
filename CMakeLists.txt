cmake_minimum_required(VERSION 3.16)
project(ugaris-native-demo-mod C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output name based on platform
if(WIN32)
    set(MOD_OUTPUT_NAME "bmod")
elseif(APPLE)
    set(MOD_OUTPUT_NAME "bmod")
else()
    set(MOD_OUTPUT_NAME "bmod")
endif()

# Create shared library
add_library(${MOD_OUTPUT_NAME} SHARED
    src/main.c
)

# Include directories
target_include_directories(${MOD_OUTPUT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Platform-specific settings
if(WIN32)
    # Windows: output as .dll
    set_target_properties(${MOD_OUTPUT_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
    # Windows: link the client's import library (lib/moac.lib or moac.a from
    # the client release's mod-sdk.zip). A DLL built with unresolved client
    # symbols (/FORCE:UNRESOLVED) loads, but the first client API call jumps
    # to a null pointer and crashes the game.
    if(EXISTS "${CMAKE_SOURCE_DIR}/lib/moac.a" AND NOT MSVC)
        target_link_libraries(${MOD_OUTPUT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/moac.a")
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/lib/moac.lib")
        target_link_libraries(${MOD_OUTPUT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/moac.lib")
    else()
        message(FATAL_ERROR "Windows builds need lib/moac.lib (or lib/moac.a) from the client mod-sdk.zip - see README")
    endif()
elseif(APPLE)
    # macOS: output as .dylib, build universal binary
    set_target_properties(${MOD_OUTPUT_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".dylib"
    )
    # Universal binary for Intel and Apple Silicon
    if(CMAKE_OSX_ARCHITECTURES STREQUAL "")
        set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for macOS")
    endif()
    # Allow undefined symbols (resolved at runtime by host application)
    target_link_options(${MOD_OUTPUT_NAME} PRIVATE -undefined dynamic_lookup)
else()
    # Linux: output as .so
    set_target_properties(${MOD_OUTPUT_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".so"
    )
    # Set visibility for symbols
    target_compile_options(${MOD_OUTPUT_NAME} PRIVATE -fvisibility=hidden)
    # Allow undefined symbols (default, but be explicit)
    target_link_options(${MOD_OUTPUT_NAME} PRIVATE -Wl,--allow-shlib-undefined)
endif()

# Compiler warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${MOD_OUTPUT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Release optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${MOD_OUTPUT_NAME} PRIVATE -O2)
    endif()
endif()

# Install target
install(TARGETS ${MOD_OUTPUT_NAME}
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

cmake_minimum_required(VERSION 3.10)
project(FruityFreefall)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio Network)

# Include directories
include_directories(src)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")


# Main executable
add_executable(FruityFreefall ${SOURCES} )

# Link SFML
target_link_libraries(FruityFreefall PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network )

# Copy assets to build directory
add_custom_command(TARGET FruityFreefall POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)

   
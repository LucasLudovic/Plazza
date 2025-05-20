cmake_minimum_required(VERSION 3.10)
project(plazza)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-unique")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_compile_options(-Wall -Wextra -Werror -pedantic)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wl,--export-dynamic")


# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(ERRORS_DIR ${SRC_DIR}/Errors)
set(UTILS_DIR ${SRC_DIR}/Utils)
set(RENDERER_DIR ${SRC_DIR}/Renderer)

# Include directories
include_directories (
    ${SRC_DIR}
    ${ERRORS_DIR}
    ${UTILS_DIR}
    ${RENDERER_DIR}
)

# Souces setter
set(SOURCES
    ${SRC_DIR}/Main.cpp

    ${SRC_DIR}/Plazza.cpp
    ${SRC_DIR}/Data.cpp

    ${RENDERER_DIR}/ShellRenderer.cpp
    ${RENDERER_DIR}/SFMLRenderer.cpp

    ${ERRORS_DIR}/AError.cpp
)

# Creating Core binary
add_executable(plazza ${SOURCES})
target_link_libraries(plazza sfml-graphics sfml-window sfml-system)
set_target_properties(plazza PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

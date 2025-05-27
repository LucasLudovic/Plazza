cmake_minimum_required(VERSION 3.10)
project(plazza)

# include(FetchContent)

# Fetch SFML
# FetchContent_Declare(
#     sfml
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG        2.6.2
# )
# FetchContent_MakeAvailable(sfml)

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
set(NETWORK_DIR ${SRC_DIR}/Network)
set(SERVER_DIR ${NETWORK_DIR}/Server)
set(CLIENT_DIR ${NETWORK_DIR}/Client)
set(KITCHEN_DIR ${SRC_DIR}/Kitchens)
set(COOKS_DIR ${KITCHEN_DIR}/Cooks)

# Include directories
include_directories (
    ${SRC_DIR}
    ${ERRORS_DIR}
    ${UTILS_DIR}
    ${RENDERER_DIR}
    ${NETWORK_DIR}
    ${SERVER_DIR}
    ${CLIENT_DIR}
    ${KITCHEN_DIR}
    ${COOKS_DIR}
)

# Souces setter
set(SOURCES
    ${SRC_DIR}/Main.cpp

    ${SRC_DIR}/Data.cpp
    ${SRC_DIR}/Plazza.cpp

    ${RENDERER_DIR}/ShellRenderer.cpp
    ${RENDERER_DIR}/SFMLRenderer.cpp

    ${NETWORK_DIR}/ANetwork.cpp
    ${NETWORK_DIR}/Client/Base.cpp
    ${NETWORK_DIR}/Client/Communication.cpp
    ${NETWORK_DIR}/Server/Base.cpp
    ${NETWORK_DIR}/Server/Communication.cpp

    ${KITCHEN_DIR}/Base.cpp
    ${KITCHEN_DIR}/Ingredient.cpp
    ${KITCHEN_DIR}/Pizza.cpp
    ${KITCHEN_DIR}/Cooks/Cooks.cpp
    ${KITCHEN_DIR}/Cooks/Cooking.cpp

    ${ERRORS_DIR}/AError.cpp
)

# Creating Core binary
add_executable(plazza ${SOURCES})
target_link_libraries(plazza sfml-graphics sfml-window sfml-system)
set_target_properties(plazza PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

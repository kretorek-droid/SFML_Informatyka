cmake_minimum_required(VERSION 3.10)
project(SFML_Informatyka)

set(CMAKE_CXX_STANDARD 20)


set(SFML_ROOT "C:/SFML-3.0.2")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")


cmake_policy(SET CMP0074 NEW)


find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(untitled main.cpp)

target_link_libraries(untitled
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)


if (WIN32)
    add_custom_command(TARGET untitled POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_ROOT}/bin"
            $<TARGET_FILE_DIR:untitled>)
endif()
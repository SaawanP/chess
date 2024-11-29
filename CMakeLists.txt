cmake_minimum_required(VERSION 3.11)
project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
add_compile_options(-Wall -Wextra -Wno-unused-result)

set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML COMPONENTS Window Graphics REQUIRED)

find_package(
    Boost
    COMPONENTS system filesystem
    REQUIRED
)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Fatal error: Boost required.\n")
endif(NOT Boost_FOUND)

add_executable(${PROJECT_NAME} src/ui_main.cpp src/chessboard.cpp src/pieces.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(
    ${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system    
    Boost::system
    Boost::filesystem
)


cmake_minimum_required(VERSION 3.0)

project(bfl)

set(CMAKE_CXX_FLASS "-std=c++11 -Wall -pthread")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(
	${PROJECT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/include
	)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# add_dependencies(-DCC=1)

message(${PROJECT_SOURCE_DIR})

aux_source_directory(src SRC)

add_executable(${PROJECT_NAME} ${SRC} test/test_config.cpp)
add_executable(test_terminal test/test_terminal.cpp)
add_executable(test_config ${SRC} test/test_config.cpp)

target_link_libraries(${PROJECT_NAME} yaml-cpp)
target_link_libraries(test_config yaml-cpp)

target_include_directories(${PROJECT_NAME} PUBLIC lib/include)



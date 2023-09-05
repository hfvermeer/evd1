cmake_minimum_required(VERSION 3.5.0)
project(exercise2_1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)

add_executable(exercise2_1 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(exercise2_1 ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
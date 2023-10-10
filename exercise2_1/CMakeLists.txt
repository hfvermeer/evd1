cmake_minimum_required(VERSION 3.5.0)
project(exercise VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

find_package(OpenCV REQUIRED)

add_executable(exercise main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(exercise ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

#
# Find Google microbenchmark support library
#
FIND_PACKAGE(benchmark REQUIRED
  HINTS ${benchmark_DIR} ${benchmark_DIR} ../ ../../ $ENV{benchmark_DIR}
)

FIND_PACKAGE(GTest REQUIRED
  HINTS ${GTest_DIR} ${GTest_DIR} ../ ../../ $ENV{GTest_DIR}
)

PROJECT(Cpp_Benchmarks)

#
# SET(SOURCES
#    source/find_element.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

ADD_EXECUTABLE(find_element source/find_element.cc)

# ADD_LIBRARY(finite_element STATIC)
TARGET_LINK_LIBRARIES(find_element
  PUBLIC benchmark::benchmark
         GTest::GTest)
TARGET_COMPILE_DEFINITIONS(find_element PUBLIC)

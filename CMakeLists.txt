
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

#
# For some reason TARGET_SUPPORTS_SHARED_LIBS isn't set sometimes.
# Setting it here explicitly.
#
SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

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

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(source)

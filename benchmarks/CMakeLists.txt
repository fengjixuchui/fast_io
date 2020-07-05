cmake_minimum_required(VERSION 3.15)
project(fastio_examples)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
add_definitions(/experimental:concepts)
#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
message(FATAL_ERROR "fast_io no longer supports GCC < 10 version because of incomplete C++ standard library support for concepts lite. Please build the master version of GCC from its official or mirror repo. Or use Visual Studio Preview")
endif()
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
add_definitions(-ffast-math -Wall -Wextra -maes -msse2 -msha)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
add_definitions(-Xclang -fconcepts-ts -ffast-math -maes -msse2 -msha)
endif()

set(CMAKE_CXX_STANDARD 20)


add_executable(output_10M_size_t "./0000.10m_size_t/output_10M_size_t.cc")
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
add_executable(tenm_size_t "./0000.10m_size_t/with_crypto/tenm_size_t.cc")
endif()
add_executable(output_10M_double "./0001.10m_double/output_10M_double.cc")

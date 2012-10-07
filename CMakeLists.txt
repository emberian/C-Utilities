cmake_minimum_required(VERSION 2.6)
project(Utilities C)

set(cutil_sources Common.c)
file(GLOB_RECURSE cutil_headers include/*.h)

include_directories(include)

add_library(Utilities SHARED ${cutil_sources})

if(MSVC)
  set(CMAKE_C_FLAGS_RELEASE "/arch:AVX /Gr /O2 /MP /Za /Fx /FAs /Fa")
  set(CMAKE_C_FLAGS_DEBUG "/arch:AVX /Od /Za /MP /FAs /Fa /Zi")
endif()

if(NOT WIN32)
  install(FILES ${cutil_headers} DESTINATION include/C-Utilities)
endif()

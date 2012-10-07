cmake_minimum_required(VERSION 2.6)
project(Utilities C)
add_library(Utilities SHARED Common.c)

# the defaults for gcc are fine
if(MSVC)
  set(CMAKE_C_FLAGS_RELEASE "/arch:AVX /Gr /O2 /MP /Za /Fx /FAs /Fa")
  set(CMAKE_C_FLAGS_DEBUG "/arch:AVX /Od /Za /MP /FAs /Fa /Zi")
endif(MSVC)


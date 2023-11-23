cmake_minimum_required(VERSION 3.11)
include(FetchContent)
FetchContent_Declare(
  whereami-external
  GIT_REPOSITORY https://github.com/gpakosz/whereami.git
  GIT_TAG        ba364cd54fd431c76c045393b6522b4bff547f50 # master @ 2023.04.20.
)
FetchContent_MakeAvailable(whereami-external)
# NOTE: This works, though not elegant
set(whereami_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/_deps/whereami-external-src/src/whereami.c")
set(whereami_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/whereami-external-src/src")
# NOTE: this would be ideal, however for some reason on the exported OpenCL::Utils
#       lib an INTERFACE_LINK_LIBRARIES $<LINK_ONLY:whereami> prop appears which
#       is nonsense, LINK_ONLY makes no sense for a dep that OpenCL::Utils linked
#       to PRIVATEly.
#
#add_library(whereami IMPORTED INTERFACE)
#target_include_directories(whereami
#  INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/_deps/whereami-external-src/src"
#)
#target_sources(whereami
#  INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/_deps/whereami-external-src/src/whereami.c"
#)

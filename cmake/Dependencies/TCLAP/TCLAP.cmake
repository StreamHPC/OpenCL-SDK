if(NOT DEPENDENCIES_FORCE_DOWNLOAD)
  find_package(TCLAP)
endif()

if(NOT TCLAP_FOUND)
  if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/_deps/tclap-external-src")
    if(DEPENDENCIES_FORCE_DOWNLOAD)
      message(STATUS "DEPENDENCIES_FORCE_DOWNLOAD is ON. Fetching TCLAP.")
    else()
      message(STATUS "Fetching TCLAP.")
    endif()
  endif()
  cmake_minimum_required(VERSION 3.11)
  include(FetchContent)
  FetchContent_Declare(
    tclap-external
    GIT_REPOSITORY      https://github.com/mirror/tclap.git
    GIT_TAG             v1.2.5 # 58c5c8ef24111072fc21fb723f8ab45d23395809
    UPDATE_COMMAND      ""
    PATCH_COMMAND       ""
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    TEST_COMMAND        ""
  )
  FetchContent_MakeAvailable(tclap-external)
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/_deps/tclap-external-src/include")
  find_package(TCLAP REQUIRED)
endif()
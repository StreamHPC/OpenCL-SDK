if(NOT DEPENDENCIES_FORCE_DOWNLOAD AND NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/_deps/glm-external-src")
  find_package(glm CONFIG)
endif()

if(NOT (glm_FOUND OR TARGET glm::glm))
  if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/_deps/glm-external-src")
    if(DEPENDENCIES_FORCE_DOWNLOAD)
      message(STATUS "DEPENDENCIES_FORCE_DOWNLOAD is ON. Fetching glm.")
    else()
      message(STATUS "Fetching glm.")
    endif()
    message(STATUS "Adding glm subproject: ${CMAKE_CURRENT_BINARY_DIR}/_deps/glm-external-src")
  endif()
  cmake_minimum_required(VERSION 3.11)
  include(FetchContent)
  FetchContent_Declare(
    glm-external
    GIT_REPOSITORY      https://github.com/g-truc/glm
    GIT_TAG             0.9.9.8 # e79109058964d8d18b8a3bb7be7b900be46692ad
  )
  FetchContent_MakeAvailable(glm-external)
endif()
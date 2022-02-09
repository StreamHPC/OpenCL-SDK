if(OPENCL_SDK_BUILD_SAMPLES)
  foreach(DEP IN ITEMS cargs TCLAP Stb)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Dependencies/${DEP}")
    include(${DEP})
  endforeach()

  if(OPENCL_SDK_BUILD_OPENGL_SAMPLES)
    foreach(DEP IN ITEMS X11 glm OpenGL)
      list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Dependencies/${DEP}")
      include(${DEP})
    endforeach()

    cmake_minimum_required(VERSION 3.10) # SFML 2 won't find Freetype::Freetype under 3.10
    find_package(GLEW REQUIRED)
    find_package(SFML 2
      REQUIRED
      COMPONENTS window graphics
    )
  endif(OPENCL_SDK_BUILD_OPENGL_SAMPLES)
endif(OPENCL_SDK_BUILD_SAMPLES)
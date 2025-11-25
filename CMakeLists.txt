cmake_minimum_required(VERSION 3.8) 

PROJECT(OpenGLBase LANGUAGES CUDA CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON) 

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(OpenGL_GL_PREFERENCE GLVND)

# If using debug mode, force no optimization and debug symbols
add_compile_options(
  "$<$<CONFIG:DEBUG>:-O0;-g>"
)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Qt6 COMPONENTS Widgets OpenGLWidgets REQUIRED)
find_package(Threads REQUIRED)


add_subdirectory(third_party/spdlog)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}/OpenGLBase_autogen/include
  ${GLEW_INCLUDE_DIRS}
)

add_executable(OpenGLBase
  src/main.cpp
  src/window.cpp
  src/openGlWidget.cpp

  src/gl/gl_utils.cpp
  src/gl/shader/shader.cpp
  src/gl/shader/graphic_shader.cpp

  src/utils/logger.cpp
)

set_property(TARGET OpenGLBase PROPERTY CXX_STANDARD 17)

# Flags for enabling high level warnings
if (MSVC)
    target_compile_options(OpenGLBase PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/W1>)
else()
    target_compile_options(OpenGLBase PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-Wall>)
endif()

set_property(TARGET OpenGLBase PROPERTY CUDA_ARCHITECTURES 60)


# Use the Widgets module from Qt 6
target_link_libraries(OpenGLBase
  PRIVATE
    Qt6::Widgets
    Qt6::OpenGLWidgets
    glm::glm
    ${OPENGL_LIBRARIES}
    GLEW::glew
    Threads::Threads
    spdlog::spdlog
)
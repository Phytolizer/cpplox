cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(fmt)
include(cmake/in-source-guard.cmake)

project(
    cpplox
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    cpplox_lib OBJECT
    source/lib.cpp
    source/scanner.cpp
    source/token.cpp
)

target_include_directories(
    cpplox_lib
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_link_libraries(cpplox_lib PUBLIC fmt::fmt)

target_compile_features(cpplox_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(cpplox_cpplox source/main.cpp)
add_executable(cpplox::cpplox ALIAS cpplox_cpplox)

set_target_properties(
    cpplox_cpplox PROPERTIES
    OUTPUT_NAME cpplox
    EXPORT_NAME cpplox
)

target_compile_features(cpplox_cpplox PRIVATE cxx_std_20)

target_link_libraries(cpplox_cpplox PRIVATE cpplox_lib)

# ---- Install rules ----

include(cmake/install-rules.cmake)

# ---- Developer mode ----

if(NOT cpplox_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of cpplox"
  )
endif()

include(cmake/dev-mode.cmake)

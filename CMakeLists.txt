cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(make-proj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB CXX_SOURCE_FILE "./src/*.cpp")
file(GLOB HEADER_FILE "./src/*.hpp")

include(FetchContent)

# Not being used right now
FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.3.0)
FetchContent_MakeAvailable(tomlplusplus)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.1.1)
FetchContent_MakeAvailable(fmt)

add_executable(${PROJECT_NAME} ${CXX_SOURCE_FILE} ${HEADER_FILE})

target_link_libraries(${PROJECT_NAME} tomlplusplus::tomlplusplus fmt)

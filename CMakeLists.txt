cmake_minimum_required(VERSION 3.24)
project(YetAnotherRaycaster)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(YetAnotherRaycaster
        src/main.cpp
        src/Rays.cpp
        src/Ray.cpp
        src/operations.cpp
        src/Particle.cpp)


if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_DIR C:/Users/mchuv/lib/SFML-2.5.1/lib/cmake/SFML)
  include_directories(C:/Users/mchuv/lib/SFML-2.5.1/include)
endif(WIN32)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(YetAnotherRaycaster sfml-graphics sfml-window sfml-system)

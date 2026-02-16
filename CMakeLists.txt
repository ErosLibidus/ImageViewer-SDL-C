cmake_minimum_required(VERSION 3.10)
project(VisorImagenC)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Visor src/main.c)

target_link_libraries(Visor ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# CMakeLists.txt
# 	for the Game15 project
#  Author: jorio@mail.com Date: May 2021

cmake_minimum_required(VERSION 3.7)

project(Game15 VERSION 1.0 DESCRIPTION "Game 15 in C++")
add_executable(game15)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_gfx REQUIRED)

include_directories(game15 INTERFACE ${SDL_INCLUDE_DIR})
include_directories(game15 INTERFACE ${SDL_TTF_LIBRARIRES})

target_sources(game15 PRIVATE main.cpp 
	Game15.cpp 
	Game15BoardView.cpp
)

# show the libs we shall link against
if(${SDL_FOUND})
	message("Value is: ${SDL_LIBRARY}")
endif()
if(${SDL_TTF_FOUND})
	message("Value is: ${SDL_TTF_LIBRARY}")
endif()
if(${SDLGFX_FOUND})
	message("Value is: ${SDLGFX_LIBRARY}")
endif()

target_link_libraries(game15 ${SDL_TTF_LIBRARY})
target_link_libraries(game15 ${SDLGFX_LIBRARY})
target_link_libraries(game15 ${SDL_LIBRARY})


cmake_minimum_required(VERSION 3.0)

set(GAME_NAME App)
#project name
project(${GAME_NAME})

#指定c++版本
add_definitions(-std=c++17)

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")

#copy assets to ./
file(COPY assets DESTINATION .)

#head file path
INCLUDE_DIRECTORIES(
        app
        module/entt/src
        module/cute_headers
)

#add c/cc/cpp files
file(GLOB_RECURSE APP_SOURCES "app/main.cpp" "app/core/*.cpp" "app/helpers/*.cpp" "app/sys/*.cpp" "app/utils/*.cpp")

#add executable file
ADD_EXECUTABLE(${GAME_NAME} ${APP_SOURCES})

#find sfml
find_package(SFML 2 COMPONENTS graphics window audio system)
if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
else()
        set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
        message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
        message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

#link library
target_link_libraries(${GAME_NAME} ${SFML_LIBRARIES})

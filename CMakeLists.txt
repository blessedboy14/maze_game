cmake_minimum_required(VERSION 3.23)
project(main)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(main main.cpp main/mainMenu.cpp main/mainMenu.h choose/choose.cpp choose/choose.h game/Game.cpp game/Game.h hero/Hero.cpp hero/Hero.h door/door.cpp door/door.h)

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-audio sfml-graphics)


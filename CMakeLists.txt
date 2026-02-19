cmake_minimum_required(VERSION 4.0)
project(Mini_Scratch)

set(CMAKE_CXX_STANDARD 20)

add_executable(Mini_Scratch main.cpp
        UI.h
        motion.h
        looks.h
        events.h
        execute.h
        variables.h
        control.h)

target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)

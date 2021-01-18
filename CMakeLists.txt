cmake_minimum_required(VERSION 3.17)
project(mosaicgame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SYSTEM_LIBRARY_PATH true)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
#find_package(GMP REQUIRED)
#find_package(GMPXX REQUIRED)

add_library(
        mosaicgame SHARED
        library.cpp
        Board/BitsetBoard.cpp
        Game/BitsetOneToOneGame.cpp
        Game/Move/BitsetMove.cpp
#        Board/GMPBoard.cpp
#        Game/GMPOneToOneGame.cpp
#        Game/Move/GMPMove.cpp
)
add_executable(
        main
        main.cpp
        Board/BitsetBoard.cpp
        Game/BitsetOneToOneGame.cpp
        Game/Move/BitsetMove.cpp
#        Board/GMPBoard.cpp
#        Game/GMPOneToOneGame.cpp
#        Game/Move/GMPMove.cpp
)

#target_link_libraries(main GMP::GMP GMPXX::GMPXX)

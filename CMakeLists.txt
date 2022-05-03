cmake_minimum_required(VERSION 3.0)

project(streetninja)

add_executable(streetninja main.cpp levelmenu.cpp levelgame.cpp game.cpp enetinterface.cpp levelque.cpp leveljoin.cpp levelhost.cpp hostlogic.cpp clientlogic.cpp)

target_include_directories(streetninja PUBLIC "include")

add_subdirectory(raylib)

target_link_libraries(streetninja raylib)

add_subdirectory(enet)

target_include_directories(enet PUBLIC enet/include)

target_link_libraries(streetninja enet)

target_compile_features(streetninja PRIVATE cxx_std_17)
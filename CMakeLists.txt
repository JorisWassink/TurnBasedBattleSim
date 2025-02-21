cmake_minimum_required(VERSION 3.26)
project(main)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Users/joris/.vcpkg-clion/vcpkg/installed/x64-windows/share/SFML")


add_executable(main
        TurnBasedBattleSim.cpp
        Player.cpp
        Scene.cpp
        PlayButton.cpp
        GenericLabel.cpp
        PlayerStats.cpp
        QuitButton.cpp
        WriteButton.cpp
        UI.cpp
        GameObject.cpp
        Button.cpp
        Character.cpp
        Enemy.cpp
        EnemyManager.cpp
        HighScoreLabel.cpp
        HighScoreLabel.hpp
        SpriteObject.cpp
        SpriteObject.hpp
        Animator.cpp
        Animator.hpp
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(main PRIVATE sfml-system sfml-graphics sfml-window)


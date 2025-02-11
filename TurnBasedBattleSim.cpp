#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Scene.hpp"
#include "QuitButton.hpp"
#include "WriteButton.hpp"
#include "GenericLabel.hpp"
#include "PlayButton.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "UI.hpp"
#include "EnemyManager.hpp"
#include "PlayerStats.hpp"

bool death = false;
int highScoreAmount = 5;
int currentScore = 0;




void SetHighScores(int highScoreAmount, int currentScore) {
    int* highScores = new int[highScoreAmount];

    //how to change directionary
    std::ifstream myFileRead("text.cmgt");

    if (myFileRead) {
        // Reset the cursor to the beginning of the file to read high scores
        myFileRead.clear(); // Clear EOF flag
        myFileRead.seekg(0); // Move cursor to the start of the file
       

        for (int i = 0; i < highScoreAmount; ++i) {
            if (!(myFileRead >> highScores[i])) {
                std::cerr << "Error reading number " << i + 1 << std::endl;
                //404 meaning an error
                highScores[i] = 404;
            }
        }

        for (int i = 0; i < highScoreAmount; ++i) {
            if (highScores[i] < currentScore) {
                int j = highScores[i];

                highScores[i] = currentScore;
                currentScore = j;
            }
        }
    }
    else {
        printf("something went wrong opening the file, it might've been deleted, im not making a new one with reset scores \n");
        std::ofstream myFileWrite("text.cmgt");

        for (unsigned int i = 1; i < 6; i++) {
            myFileWrite << "0 ";
        }
        myFileWrite.close();
    }

    std::ofstream myFileWrite("text.cmgt");

    for (unsigned int i = 0; i < 5; i++) {
        myFileWrite << std::to_string(highScores[i]) + " ";
    }
    myFileWrite.close();

    myFileRead.close();
    delete[] highScores;
}



std::string GetHighScores(int highScoreAmount) {
    int* highScores = new int[highScoreAmount];

    //how to change directionary
    std::ifstream myFileRead("text.cmgt");

    if (myFileRead) {
        // Reset the cursor to the beginning of the file to read high scores
        myFileRead.clear(); // Clear EOF flag
        myFileRead.seekg(0); // Move cursor to the start of the file

        for (int i = 0; i < highScoreAmount; ++i) {
            if (!(myFileRead >> highScores[i])) {
                std::cerr << "Error reading number " << i + 1 << std::endl;
                //404 meaning an error
                highScores[i] = 404;
            }
        }
    }
    else {
        printf("something went wrong opening the file, it mightve been deleted, im now making a new one with reset scores \n");
        std::ofstream myFileWrite("text.cmgt");

        for (unsigned int i = 1; i < 6; i++) {
            myFileWrite << "0 ";
        }
        myFileWrite.close();
        return GetHighScores(highScoreAmount);
    }


    std::string highScoreText;

    for (unsigned int i = 0; i < highScoreAmount; i++)
    {
        highScoreText += "Highscore " + std::to_string(i + 1) + ": " + std::to_string(highScores[i]) + "\n";
    }

    myFileRead.close();
    delete[] highScores;

    return highScoreText;
}

void Player::CheckDeath() {
    if (health <= 0) {
        death = true;
        SetHighScores(highScoreAmount, pScore);
        currentScore = pScore;
        pScore = 0;
        Initialize(body.getPosition(), body.getScale(), body.getColor());

    }
}

int main() {
    float screenWidth = 1920;
    float screenHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "epic game");
    sf::Font font;
    
    
    font.loadFromFile("arial.ttf");

    std::string highScoresText = GetHighScores(highScoreAmount);

    Scene mainMenu("MainMenu");
    Scene characterScene("characterSelect001");
    Scene levelOneScene("level1");
    Scene GameOverScene("GameOver001");

#pragma region mainmenu
    GenericLabel title("Joris' Super Awesome cool Battle Simulator", sf::Vector2f(screenWidth / 2, 100));
    GenericLabel credit("(Art assets by Iben the art dude)", sf::Vector2f(screenWidth / 2, 125));

    GenericLabel highScores(highScoresText, sf::Vector2f(90, 90));
    
    WriteButton writeButton("lodButton", font, "RESET SCORES",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        "text.cmgt", sf::Vector2f(0, 0));

    QuitButton quitButton("QuitButton1", font, "QUIT",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        sf::Vector2f(1720, 0));

    PlayButton selectButton("play001", font, "play",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        sf::Vector2f(screenWidth - 200, 1030), &mainMenu, &levelOneScene);

    #pragma region AddStuff
    mainMenu.addGameObject(writeButton);
    mainMenu.addGameObject(title);
    mainMenu.addGameObject(credit);
    mainMenu.addGameObject(quitButton);
    mainMenu.addGameObject(highScores);
    mainMenu.addGameObject(selectButton);
    #pragma endregion


#pragma endregion

#pragma region character select
    PlayButton playButton("play002", font, "play",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        sf::Vector2f(screenWidth - 200, 1030), &mainMenu, &levelOneScene);

    PlayButton backToMenuButton("back002", font, "cancel",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Blue, window,
        sf::Vector2f(0, 1030), &mainMenu, &levelOneScene);

    PlayerStats stats("stats001", 
        sf::Vector2f(screenWidth/2, screenHeight/2),
        sf::Vector2f(300, 0));

    #pragma region add stuff
    characterScene.addGameObject(backToMenuButton);
    characterScene.addGameObject(playButton);
    characterScene.addGameObject(stats);
    #pragma endregion
    
#pragma endregion

#pragma region GameOver
    GenericLabel GameOverText("Game Over\nfinal score: " + std::to_string(currentScore), sf::Vector2f(screenWidth / 2, screenHeight / 2));
    #pragma region AddStuff
    GameOverScene.addGameObject(GameOverText);
    GameOverScene.addGameObject(backToMenuButton);
    #pragma endregion
#pragma endregion

#pragma region LevelOne
    GenericLabel textLine("Fight!\n", sf::Vector2f(screenHeight / 2, screenHeight / 2));

    PlayButton backButton("back001", font, "back",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Blue, window,
        sf::Vector2f(0, 1030), &mainMenu, &levelOneScene);

    sf::Texture texture;
    texture.loadFromFile("textures/player.png");
    texture.setSmooth(true);
    Player player(sf::Vector2f(screenWidth / 5, screenHeight / 5),
        sf::Vector2f(.5f, .5f),
        sf::Color::White, texture);


    EnemyManager manager("manager001", sf::Vector2f(screenWidth / 2, screenHeight / 5), textLine);

    UI ui("ui", &player, manager.GetEnemy());


    #pragma region add stuff
    levelOneScene.addGameObject(ui);
    levelOneScene.addGameObject(backButton);
    levelOneScene.addGameObject(player);
    levelOneScene.addGameObject(manager);
    levelOneScene.addGameObject(textLine);
    #pragma endregion
#pragma endregion


    Scene* currentScene = &mainMenu;


    selectButton.setButtonAction([&]() {
        currentScene = &characterScene;
    });

    playButton.setButtonAction([&]() {
        player.SetStats(stats.getStats());
        if (FastestCharacter(&player, manager.GetEnemy()) == &player) {
            
        }
        else {
            manager.EnemyTurn(&player);
        }
        currentScene = &levelOneScene;
    });

    backButton.setButtonAction([&]() {
        currentScene = &mainMenu;
    });

    backToMenuButton.setButtonAction([&]() {
        death = false;
        manager.GetEnemy()->Initialize(*manager.GetEnemy());
        currentScene = &mainMenu;
        
    });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                currentScene->HandleObjectEvents(event, window);
                ui.HandleObjectEvents(event, window);
            }
        }
        highScores.textStr = GetHighScores(5);
        window.clear();
        currentScene->render(window);
        currentScene->update();
        window.display();

        if (death) {
            GameOverText.textStr = "Game Over\nfinal score: " + std::to_string(currentScore);
            currentScene = &GameOverScene;
        }
    }
    return 0;
}


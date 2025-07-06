#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "QuitButton.hpp"
#include "WriteButton.hpp"
#include "GenericLabel.hpp"
#include "PlayButton.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "UI.hpp"
#include "EnemyManager.hpp"
#include "HighScoreLabel.hpp"
#include "PlayerStats.hpp"
#include "SpriteObject.hpp"

static bool death = false;
static int highScoreAmount = 5;
static int currentScore = 0;



bool Player::CheckDeath() {
    if (health <= 0) {
        death = true;
        HighScoreLabel::SetHighScores(highScoreAmount, pScore);
        currentScore = pScore;
        pScore = 0;
        Initialize(body.getPosition(), body.getScale(), body.getColor());
        return true;
    }
    return false;
}

int main() {
    int screenWidth = 1920;
    int screenHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "epic game");
    sf::Font font;

    Scene mainMenu("MainMenu001");
    Scene characterScene("characterSelect001");
    Scene levelOneScene("level1");
    Scene botBattleScene("botBattle");
    Scene GameOverScene("GameOver001");
    Scene* currentScene = &mainMenu;


#pragma region mainmenu
    sf::Texture bgTexture;
    bgTexture.loadFromFile("Textures/bg.png");
    sf::Sprite background(bgTexture, sf::IntRect(0, 0, screenWidth, screenHeight));
    SpriteObject bgObject("background001", background);

    GenericLabel title("Joris' Super Awesome cool Battle Simulator", sf::Vector2f(screenWidth / 2.0f, 100));
    GenericLabel credit("(Art assets by Iben the art dude)", sf::Vector2f(screenWidth / 2.0f, 125));

    HighScoreLabel highScores("highScoreText001", sf::Vector2f(20, 90), font, sf::Color::Green, window, "text.cmgt");
    
    WriteButton writeButton("loadButton001", font, "RESET SCORES",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        "text.cmgt", sf::Vector2f(0, 0));

    QuitButton quitButton("QuitButton001", font, "QUIT",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        sf::Vector2f(1720, 0));

    PlayButton selectButton("play001", font, "play",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Red, window,
        sf::Vector2f(screenWidth - 200, 1030), &mainMenu, &levelOneScene);

    #pragma region AddStuff
    mainMenu.addGameObject(bgObject);
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

    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");
    playerTexture.setSmooth(true);
    Player player(sf::Vector2f(screenWidth / 5, screenHeight / 5),
        sf::Vector2f(.5f, .5f),
        sf::Color::White, playerTexture, "player");


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

#pragma region BotBattle
    GenericLabel textLine2("Fight!\n", sf::Vector2f(screenHeight / 2, screenHeight / 2));

    PlayButton backButton2("back001", font, "back",
        sf::Vector2f(200.0f, 50.0f),
        sf::Color::Blue, window,
        sf::Vector2f(0, 1030), &mainMenu, &levelOneScene);

    sf::Texture playerTexture2;
    playerTexture2.loadFromFile("textures/player.png");
    playerTexture2.setSmooth(true);


    EnemyManager manager2("manager001", sf::Vector2f(screenWidth / 5, screenHeight / 5), textLine2);

    EnemyManager manager3("manager002", sf::Vector2f(screenWidth / 2, screenHeight / 5), textLine2);




#pragma region add stuff
    botBattleScene.addGameObject(backButton2);
    botBattleScene.addGameObject(manager2);
    botBattleScene.addGameObject(manager3);
    botBattleScene.addGameObject(textLine2);
#pragma endregion
#pragma endregion


    font.loadFromFile("arial.ttf");

    selectButton.setButtonAction([&]() {
        currentScene = &characterScene;
    });


    playButton.setButtonAction([&]() {
        player.SetStats(stats.getStats());
    if (FastestCharacter(manager.GetEnemy(), &player) == manager.GetEnemy()) {
        manager.EnemyTurn(&player);
    }
    else {
        player.Turn(manager.GetEnemy());
    }
    currentScene = &levelOneScene;
});

    // playButton.setButtonAction([&]() {
    // if (FastestCharacter(manager3.GetEnemy(), manager2.GetEnemy()) == manager3.GetEnemy()) {
    //     manager3.EnemyTurn(manager2.GetEnemy());
    // }
    // else {
    //     manager2.EnemyTurn(manager3.GetEnemy());
    // }
    //     currentScene = &botBattleScene;
    // });

    backButton.setButtonAction([&]() {
        currentScene = &mainMenu;
    });

    backToMenuButton.setButtonAction([&]() {
        death = false;
        manager.GetEnemy()->Initialize();
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
        highScores.textStr = HighScoreLabel::GetHighScores(5);
        window.clear();
        currentScene->update();
        currentScene->render(window);
        window.display();

        if (death) {
            GameOverText.textStr = "Game Over\n final score: " + std::to_string(currentScore);
            currentScene = &GameOverScene;
        }
    }
    return 0;
}


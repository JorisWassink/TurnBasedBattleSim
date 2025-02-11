#pragma once
#include "HighScoreLabel.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <fstream>
#include <iostream>

std::string HighScoreLabel::document = "";

// Constructor
HighScoreLabel::HighScoreLabel(std::string identifier, sf::Vector2f position, sf::Font& font, sf::Color textColor, sf::RenderWindow& window, std::string doc)
: GenericLabel(identifier, position), font(font) {

    text.setFont(font);
    text.setString(GetHighScores(5));
    text.setCharacterSize(24);
    text.setFillColor(textColor);
    text.setOrigin(-position);

    document = doc;
}

void HighScoreLabel::SetHighScores(int highScoreAmount, int currentScore) {
    auto highScores = new int[highScoreAmount];
    std::ifstream myFileRead(document);

    if (myFileRead) {
        myFileRead.clear();
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



std::string HighScoreLabel::GetHighScores(int highScoreAmount) {
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

// Destructor
HighScoreLabel::~HighScoreLabel() = default;

// Update
void HighScoreLabel::update() { }

// Render the button and its text
void HighScoreLabel::render(sf::RenderWindow& window) {
    window.draw(text);
}


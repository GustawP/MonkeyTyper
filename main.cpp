#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <filesystem>
#include <set>
#include <fstream>
#include <sstream>

auto collision(std::vector<sf::Text> &words, sf::RectangleShape &border, int &points, int &lostPoints) -> void {
    for (auto it = words.begin(); it != words.end();) {
        if (it->getGlobalBounds().intersects(border.getGlobalBounds())) {
            lostPoints++;
            it = words.erase(it);
        } else {
            ++it;
        }
    }
}

void saveScore(int score) {
    std::ofstream outFile("scores.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << score << std::endl;
    }
    outFile.close();
}

std::vector<int> getTopScores() {
    std::vector<int> scores;
    std::ifstream inFile("scores.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        scores.push_back(std::stoi(line));
    }
    inFile.close();
    std::sort(scores.rbegin(), scores.rend());
    if (scores.size() > 5) {
        scores.resize(5);
    }
    return scores;
}

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    auto points = 0;
    auto lostPoints = 0;
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<std::string> library{
            "monkey", "banana", "jungle", "apple", "orange", "elephant", "tiger", "giraffe",
            "pineapple", "watermelon", "coconut", "mango", "lion", "zebra", "leopard", "chimpanzee",
            "rhinoceros", "hippopotamus", "crocodile", "alligator", "parrot", "peacock", "flamingo",
            "ostrich", "eagle", "vulture", "pelican", "swan", "duck", "goose", "bat", "frog", "toad",
            "snake", "lizard", "iguana", "chameleon", "spider", "scorpion", "bee", "ant", "butterfly",
            "moth", "cricket", "grasshopper", "beetle", "ladybug", "firefly", "dragonfly", "mosquito",
            "fly", "worm", "snail", "slug", "fish", "shark", "dolphin", "whale", "octopus", "squid",
            "crab", "lobster", "jellyfish", "starfish", "seal", "penguin", "walrus", "otter", "platypus"
    };

    sf::Font font1, font2, font3;

    std::string fontPath1 = "../mytype.ttf";
    std::string fontPath2 = "../Pixellettersfull-BnJ5.ttf";
    std::string fontPath3 = "../KOMIKABG.ttf";
    std::cout << "Loading font1 from: " << fontPath1 << std::endl;
    std::cout << "Loading font2 from: " << fontPath2 << std::endl;
    std::cout << "Loading font3 from: " << fontPath3 << std::endl;

    if (!font1.loadFromFile(fontPath1) || !font2.loadFromFile(fontPath2) || !font3.loadFromFile(fontPath3)) {
        std::cerr << "Error loading fonts" << std::endl;
        return -1;
    }

    // Font Selection Window
    sf::RenderWindow fontWindow(sf::VideoMode(800, 600), "Select Font", sf::Style::Default);
    fontWindow.setFramerateLimit(60);

    sf::Text fontMenuText("Choose a font and press Enter:", font1, 30);
    fontMenuText.setPosition(50, 50);
    fontMenuText.setFillColor(sf::Color::White);

    sf::Text fontOption1("1. Font 1", font1, 24);
    fontOption1.setPosition(50, 150);
    fontOption1.setFillColor(sf::Color::White);

    sf::Text fontOption2("2. Font 2", font2, 36);
    fontOption2.setPosition(50, 215);
    fontOption2.setFillColor(sf::Color::White);

    sf::Text fontOption3("3. Font 3", font3, 24);
    fontOption3.setPosition(50, 310);
    fontOption3.setFillColor(sf::Color::White);

    sf::Font selectedFont = font1;
    bool fontSelected = false;

    while (fontWindow.isOpen() && !fontSelected) {
        sf::Event event;
        while (fontWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fontWindow.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    selectedFont = font1;
                } else if (event.key.code == sf::Keyboard::Num2) {
                    selectedFont = font2;
                } else if (event.key.code == sf::Keyboard::Num3) {
                    selectedFont = font3;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    fontSelected = true;
                    fontWindow.close();
                }
            }
        }

        fontWindow.clear(sf::Color::Black);
        fontWindow.draw(fontMenuText);
        fontWindow.draw(fontOption1);
        fontWindow.draw(fontOption2);
        fontWindow.draw(fontOption3);
        fontWindow.display();
    }

    // Font Size Selection Window
    sf::RenderWindow sizeWindow(sf::VideoMode(800, 600), "Select Font Size", sf::Style::Default);
    sizeWindow.setFramerateLimit(60);

    sf::Text sizeMenuText("Enter font size and press Enter:", selectedFont, 30);
    sizeMenuText.setPosition(50, 50);
    sizeMenuText.setFillColor(sf::Color::White);

    sf::Text sizeInput("", selectedFont, 24);
    sizeInput.setPosition(50, 150);
    sizeInput.setFillColor(sf::Color::White);

    std::string sizeStr;
    unsigned int fontSize = 24;
    bool sizeSelected = false;

    while (sizeWindow.isOpen() && !sizeSelected) {
        sf::Event event;
        while (sizeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                sizeWindow.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    try {
                        fontSize = std::stoi(sizeStr);
                        sizeSelected = true;
                        sizeWindow.close();
                    } catch (...) {
                        sizeStr.clear(); // Reset size input on invalid entry
                        sizeInput.setString(sizeStr);
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (std::isdigit(event.text.unicode)) {
                    sizeStr += event.text.unicode;
                    sizeInput.setString(sizeStr);
                } else if (event.text.unicode == '\b' && !sizeStr.empty()) {
                    sizeStr.pop_back();
                    sizeInput.setString(sizeStr);
                }
            }
        }

        sizeWindow.clear(sf::Color::Black);
        sizeWindow.draw(sizeMenuText);
        sizeWindow.draw(sizeInput);
        sizeWindow.display();
    }

    // Main Game Window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Monkey Type", sf::Style::Default);
    window.setFramerateLimit(60);

    std::vector<sf::Text> currentWords;
    std::vector<char> writtenWord;
    sf::Text typedText("", selectedFont, fontSize); // Text to display the typed characters
    typedText.setPosition(10, window.getSize().y - 45); // Position it in the bottom left corner
    typedText.setFillColor(sf::Color::White);

    sf::Text scoreText("Score: 0", selectedFont, fontSize); // Text to display the score
    scoreText.setPosition(10, 10); // Position it in the upper left corner
    scoreText.setFillColor(sf::Color::White);

    sf::Text lostPointsText("Lost: 0", selectedFont, fontSize); // Text to display the lost points
    lostPointsText.setPosition(window.getSize().x - 100, 10); // Position it in the upper right corner
    lostPointsText.setFillColor(sf::Color::White);

    auto frameCounter = 0;
    auto spawnInterval = 180; // Initial interval to spawn new words (frames)
    const float initialWordSpeed = 0.3f; // Initial speed of words
    float wordSpeed = initialWordSpeed;
    const int speedIncreaseInterval = 800; // Interval to increase speed (frames)

    std::set<int> usedPositions; // To track used positions and avoid overlap

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !writtenWord.empty()) {
                    writtenWord.pop_back();
                } else if (event.text.unicode < 128 && std::isalpha(event.text.unicode)) {
                    writtenWord.push_back(std::tolower(static_cast<char>(event.text.unicode)));
                }
                typedText.setString(std::string(writtenWord.begin(), writtenWord.end())); // Update typed text display
            }
        }

        frameCounter++;
        if (frameCounter % spawnInterval == 0) {
            auto index = rand() % library.size();
            sf::Text newWord(library[index], selectedFont, fontSize);

            int positionY;
            do {
                positionY = rand() % (window.getSize().y - 100); // Ensure full window height is used
            } while (usedPositions.find(positionY) != usedPositions.end());

            usedPositions.insert(positionY);

            newWord.setPosition(0, positionY);
            newWord.setFillColor(sf::Color::White);
            currentWords.push_back(newWord);

            // Decrease the spawn interval to make words appear faster over time
            if (spawnInterval > 20) { // Minimum spawn interval
                spawnInterval -= 1;
            }
        }

        if (frameCounter % speedIncreaseInterval == 0) {
            wordSpeed += 0.05f; // Increase the speed of the words
        }

        for (auto &word: currentWords) {
            word.move(wordSpeed, 0); // Move words at the current speed
        }

        // Check for word matches
        auto writtenStr = std::string(writtenWord.begin(), writtenWord.end());
        for (auto it = currentWords.begin(); it != currentWords.end();) {
            if (it->getString() == writtenStr) {
                points++;
                usedPositions.erase(static_cast<int>(it->getPosition().y)); // Free up the position
                it = currentWords.erase(it);
                writtenWord.clear();
                typedText.setString(""); // Clear the typed text display
            } else {
                ++it;
            }
        }

        sf::RectangleShape border(sf::Vector2f(1, static_cast<float>(window.getSize().y)));
        border.setFillColor(sf::Color::Black);
        border.setPosition(990, 0); // Adjusted for larger window size

        collision(currentWords, border, points, lostPoints);

        // Update the score and lost points display
        scoreText.setString("Score: " + std::to_string(points));
        lostPointsText.setString("Lost: " + std::to_string(lostPoints));
        lostPointsText.setPosition(window.getSize().x - lostPointsText.getGlobalBounds().width - 10, 10);

        // End the game if lost points reach 10
        if (lostPoints >= 10) {
            saveScore(points);
            auto topScores = getTopScores();

            sf::Text gameOverText("Game Over!", selectedFont, fontSize + 26); // Adjust size for "Game Over" text
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2 - 50);

            std::stringstream ss;
            ss << "Top Scores:\n";
            for (auto i = 0; i < topScores.size(); ++i) {
                ss << i + 1 << ". " << topScores[i] << "\n";
            }

            sf::Text scoreBoardText(ss.str(), selectedFont, fontSize);
            scoreBoardText.setFillColor(sf::Color::White);
            scoreBoardText.setPosition(window.getSize().x / 2 - scoreBoardText.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);

            window.clear(sf::Color::Black);
            window.draw(gameOverText);
            window.draw(scoreBoardText);
            window.display();
            sf::sleep(sf::seconds(10)); // Delay to show "Game Over" message and scores
            window.close();
        }

        window.clear(sf::Color::Black);
        for (auto &word: currentWords) {
            window.draw(word);
        }
        window.draw(typedText); // Draw the typed text
        window.draw(scoreText); // Draw the score
        window.draw(lostPointsText); // Draw the lost points
        window.display();
    }
    return 0;
}

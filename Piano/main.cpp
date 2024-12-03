#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> //SFML Libraries

#include "src/include/header/piano.h"
#include "src/include/header/blackOctave.h"
#include "src/include/header/whiteOctave.h"
#include "src/include/header/whiteKey.h"
#include "src/include/header/blackKey.h"
#include "src/include/header/key.h"

#include <iostream>
#include <fstream>

const int WINDOW_WIDTH = 1380;
const int WINDOW_HEIGHT = 400;
const std::string FILE_PATH = "src/assets/sound.ogg";
const std::string Font_Path = "src/assets/1.otf"; // PROGRAM VARIABLE CAN BE CHANGED
const double WHITE_FREQ[] = {261.630, 293.665, 329.628, 349.228, 391.995, 440.000, 493.883};
const double BLACK_FREQ[] = {277.183, 311.127, 369.994, 415.305, 466.160};
const double BASE_FREQ = 261.63;

sf::Clock debounceClock;
sf::Time debounceTime = sf::milliseconds(1);
bool key_press = false; // FIle Handling Variables
std::string Sequence;
int keyCount;

void pressedkey(char key, std::string &keysequence, int &keycount) // Function for File Handling
{
    std::ofstream outfile;
    outfile.open("pressed_keys.txt", std::ofstream::app);

    if (outfile.is_open())
    {
        outfile << "Key pressed: " << key << std::endl;

        outfile.close();
        keysequence += key;
        keycount++;
    }
    else
    {
        std::cout << "Error opening file for writing." << std::endl;
    }
}

Key::Key()
{
    sound = new sf::Sound();
    rect = new sf::RectangleShape();
    rect->setOutlineColor(sf::Color::Black);
    rect->setOutlineThickness(2);

    isPlaying = false;
}
Key::~Key()
{
    delete rect;
    delete sound;
}
void Key::press() // Key Class Defination
{
    if (!isPlaying)
    {
        sound->stop();
        sound->play();
        isPlaying = true;
        if (rect->getFillColor() == sf::Color::White)
        {
            rect->setFillColor(sf::Color(200, 200, 200));
        }
        else if (rect->getFillColor() == sf::Color::Black)
        {
            rect->setFillColor(sf::Color(50, 50, 50));
        }
    }
}
void Key::draw()
{
    window->draw(*rect);
}
void Key::stopPressing()
{
    if (rect->getFillColor() == sf::Color(200, 200, 200))
    {
        rect->setFillColor(sf::Color::White);
    }
    else if (rect->getFillColor() == sf::Color(50, 50, 50))
    {
        rect->setFillColor(sf::Color::Black);
    }
    isPlaying = false;
}

WhiteKey::WhiteKey() {}
WhiteKey::WhiteKey(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, int position, double pitch) // White Key Class Defination
{
    window = renderWindow;

    sound->setBuffer(*soundBuffer);
    sound->setPitch(pitch);

    rect->setSize(sf::Vector2f(60, 200));
    rect->setFillColor(sf::Color::White);
    rect->setPosition(sf::Vector2f((octaveNumber * 7 + 1 + position) * 60, WINDOW_HEIGHT / 2 - 20));
}
WhiteKey::~WhiteKey() {}

BlackKey::BlackKey() {}
BlackKey::BlackKey(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, int position, double pitch) // Black Key Class Defination
{
    window = renderWindow;
    sound->setBuffer(*soundBuffer);
    sound->setPitch(pitch);
    double offset;
    switch (position)
    {
    case 0:
        offset = 1;
        break;
    case 1:
        offset = 2;
        break;
    case 2:
        offset = 4;
        break;
    case 3:
        offset = 5;
        break;
    case 4:
        offset = 6;
        break;
    }
    double xPos = 60 * (1 + octaveNumber * 7 + offset) - 40 / 2 - 2;

    rect->setSize(sf::Vector2f(40, 180));
    rect->setFillColor(sf::Color::Black);
    rect->setPosition(sf::Vector2f(xPos, 180 / 2));
}
BlackKey::~BlackKey() {}

WhiteOctave::WhiteOctave() {}
WhiteOctave::WhiteOctave(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, const double frequency[]) // WhiteOctave Class Defination
{
    for (int i = 0; i < 7; i++)
    {
        key[i] = new WhiteKey(renderWindow, soundBuffer, octaveNumber, i, (frequency[i] / BASE_FREQ));
    }
}
WhiteOctave::~WhiteOctave()
{
    for (int i = 0; i < 7; i++)
    {
        delete key[i];
    }
}
void WhiteOctave::draw()
{
    for (int i = 0; i < 7; i++)
    {
        key[i]->draw();
    }
}
void WhiteOctave::presskey(int keynum)
{
    key[keynum]->press();
}
void WhiteOctave::stopKeypress(int keynum)
{
    key[keynum]->stopPressing();
}

BlackOctave::BlackOctave() {}
BlackOctave::BlackOctave(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, const double frequency[]) // Black Ocatve CLass Defination
{
    for (int i = 0; i < 5; i++)
    {
        keys[i] = new BlackKey(renderWindow, soundBuffer, octaveNumber, i, (frequency[i] / BASE_FREQ));
    }
}
BlackOctave::~BlackOctave()
{
    for (int i = 0; i < 5; i++)
    {
        delete keys[i];
    }
}
void BlackOctave::draw()
{
    for (int i = 0; i < 5; i++)
    {
        keys[i]->draw();
    }
}
void BlackOctave::presskey(int keynum)
{
    keys[keynum]->press();
}
void BlackOctave::stopKeypress(int keynum)
{
    keys[keynum]->stopPressing();
}

Piano::Piano() // Piano Class Defination
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Piano");
    window->setFramerateLimit(20);

    background = new sf::RectangleShape();
    background->setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background->setPosition(sf::Vector2f(0, 0));
    background->setFillColor(sf::Color(80, 80, 80));

    if (!font.loadFromFile(Font_Path))
    {
        std::cout << "Error loading font file" << std::endl;
        exit(-1);
    }
    InvalidText = new sf::Text();
    InvalidText->setFont(font);
    InvalidText->setFillColor(sf::Color::Red);
    InvalidText->setCharacterSize(24);
    InvalidText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 50));
    InvalidText->setString("Invalid Input");

    isInvalid = false;

    soundBuffer = new sf::SoundBuffer();
    if (!soundBuffer->loadFromFile(FILE_PATH))
    {
        std::cout << "Cant load file.";
        exit(-1);
    }

    double lowerWF[7], upperWF[7], lowerBF[5], upperBF[5];

    for (int i = 0; i < 7; i++)
    {
        lowerWF[i] = WHITE_FREQ[i] / 2;
        upperWF[i] = WHITE_FREQ[i] * 2;
    }
    for (int i = 0; i < 5; i++)
    {
        lowerBF[i] = BLACK_FREQ[i] / 2;
        upperBF[i] = BLACK_FREQ[i] * 2;
    }
    whiteOctaves[0] = new WhiteOctave(window, soundBuffer, 0, upperWF);
    whiteOctaves[1] = new WhiteOctave(window, soundBuffer, 1, WHITE_FREQ);
    whiteOctaves[2] = new WhiteOctave(window, soundBuffer, 2, lowerWF);

    blackOctaves[0] = new BlackOctave(window, soundBuffer, 0, upperBF);
    blackOctaves[1] = new BlackOctave(window, soundBuffer, 1, BLACK_FREQ);
    blackOctaves[2] = new BlackOctave(window, soundBuffer, 2, lowerBF);
}
Piano::~Piano()
{
    delete background;
    for (int i = 0; i < 3; i++)
    {
        delete whiteOctaves[i];
        delete blackOctaves[i];
    }
    delete soundBuffer;
    delete InvalidText;
    delete window;
}
void Piano::Play()
{
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (!key_press && debounceClock.getElapsedTime() > debounceTime)
                {
                    key_press = true;
                    handleInput();
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                key_press = false;
                isInvalid = false;
                debounceClock.restart();
            }
            handleKeyboard();
            display();
        }
    }
}
void Piano::handleKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        whiteOctaves[0]->presskey(0);
    else
        whiteOctaves[0]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        whiteOctaves[0]->presskey(1);
    else
        whiteOctaves[0]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        whiteOctaves[0]->presskey(2);
    else
        whiteOctaves[0]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        whiteOctaves[0]->presskey(3);
    else
        whiteOctaves[0]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        whiteOctaves[0]->presskey(4);
    else
        whiteOctaves[0]->stopKeypress(4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        whiteOctaves[0]->presskey(5);
    else
        whiteOctaves[0]->stopKeypress(5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        whiteOctaves[0]->presskey(6);
    else
        whiteOctaves[0]->stopKeypress(6);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        blackOctaves[0]->presskey(0);
    else
        blackOctaves[0]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        blackOctaves[0]->presskey(1);
    else
        blackOctaves[0]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        blackOctaves[0]->presskey(2);
    else
        blackOctaves[0]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        blackOctaves[0]->presskey(3);
    else
        blackOctaves[0]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
        blackOctaves[0]->presskey(4);
    else
        blackOctaves[0]->stopKeypress(4);

    // Normal Octave
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        whiteOctaves[1]->presskey(0);
    else
        whiteOctaves[1]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        whiteOctaves[1]->presskey(1);
    else
        whiteOctaves[1]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        whiteOctaves[1]->presskey(2);
    else
        whiteOctaves[1]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        whiteOctaves[1]->presskey(3);
    else
        whiteOctaves[1]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        whiteOctaves[1]->presskey(4);
    else
        whiteOctaves[1]->stopKeypress(4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        whiteOctaves[1]->presskey(5);
    else
        whiteOctaves[1]->stopKeypress(5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
        whiteOctaves[1]->presskey(6);
    else
        whiteOctaves[1]->stopKeypress(6);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        blackOctaves[1]->presskey(0);
    else
        blackOctaves[1]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        blackOctaves[1]->presskey(1);
    else
        blackOctaves[1]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
        blackOctaves[1]->presskey(2);
    else
        blackOctaves[1]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        blackOctaves[1]->presskey(3);
    else
        blackOctaves[1]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
        blackOctaves[1]->presskey(4);
    else
        blackOctaves[1]->stopKeypress(4);

    // Upper Octave
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        whiteOctaves[2]->presskey(0);
    else
        whiteOctaves[2]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        whiteOctaves[2]->presskey(1);
    else
        whiteOctaves[2]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        whiteOctaves[2]->presskey(2);
    else
        whiteOctaves[2]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        whiteOctaves[2]->presskey(3);
    else
        whiteOctaves[2]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        whiteOctaves[2]->presskey(4);
    else
        whiteOctaves[2]->stopKeypress(4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
        whiteOctaves[2]->presskey(5);
    else
        whiteOctaves[2]->stopKeypress(5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        whiteOctaves[2]->presskey(6);
    else
        whiteOctaves[2]->stopKeypress(6);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        blackOctaves[2]->presskey(0);
    else
        blackOctaves[2]->stopKeypress(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        blackOctaves[2]->presskey(1);
    else
        blackOctaves[2]->stopKeypress(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        blackOctaves[2]->presskey(2);
    else
        blackOctaves[2]->stopKeypress(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        blackOctaves[2]->presskey(3);
    else
        blackOctaves[2]->stopKeypress(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote))
        blackOctaves[2]->presskey(4);
    else
        blackOctaves[2]->stopKeypress(4);
}
void Piano::handleInput()
{
    if (event.key.scancode == sf::Keyboard::Scan::Num1)
        pressedkey('1', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num2)
        pressedkey('2', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num3)
        pressedkey('3', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num4)
        pressedkey('4', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num5)
        pressedkey('5', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num6)
        pressedkey('6', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num7)
        pressedkey('7', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num8)
        pressedkey('8', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num9)
        pressedkey('9', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Num0)
        pressedkey('0', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Q)
        pressedkey('Q', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::W)
        pressedkey('W', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::E)
        pressedkey('E', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::R)
        pressedkey('R', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::T)
        pressedkey('T', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Y)
        pressedkey('Y', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::U)
        pressedkey('U', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::I)
        pressedkey('I', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::O)
        pressedkey('O', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::P)
        pressedkey('P', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::A)
        pressedkey('A', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::S)
        pressedkey('S', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::D)
        pressedkey('D', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::F)
        pressedkey('F', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::G)
        pressedkey('G', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::H)
        pressedkey('H', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::J)
        pressedkey('J', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::K)
        pressedkey('K', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::L)
        pressedkey('L', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Hyphen)
        pressedkey('-', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Equal)
        pressedkey('=', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::LBracket)
        pressedkey('[', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::RBracket)
        pressedkey(']', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Semicolon)
        pressedkey(';', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Apostrophe)
        pressedkey('\'', Sequence, keyCount);
    else if (event.key.scancode == sf::Keyboard::Scan::Enter)
        pressedkey('|', Sequence, keyCount);
    else
        isInvalid = true;
}
void Piano::display()
{
    window->clear();
    window->draw(*background);
    for (int i = 0; i < 3; i++)
    {
        whiteOctaves[i]->draw();
        blackOctaves[i]->draw();
    }
    if (isInvalid)
    {
        window->draw(*InvalidText);
    }
    window->display();
}

int main(int argc, char **argv)
{
    sf::Clock clock;

    Piano piano;
    piano.Play();
    sf::Time elapsed = clock.getElapsedTime();
    std::ofstream outfile;
    outfile.open("pressed_keys.txt", std::ofstream::app);
    if (outfile.is_open())
    {
        outfile << "Total number of keys pressed " << keyCount << std::endl;
        outfile << "Elapsed time: " << elapsed.asSeconds() << " seconds " << std::endl;
        outfile << "Entire Sequence: " << Sequence << std::endl;
        outfile << "------------------------------------------------------------------------------------" << std::endl;
        outfile.close();
    }

    return EXIT_SUCCESS;
}

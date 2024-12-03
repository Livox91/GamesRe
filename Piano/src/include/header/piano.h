#ifndef PIANO_H_INCLUDED
#define PIANO_H_INCLUDED
#include "whiteOctave.h"
#include "blackOctave.h"
class Piano
{
private:
    sf::RenderWindow *window;
    sf::Event event;
    sf::RectangleShape *background;
    sf::SoundBuffer *soundBuffer;
    sf::Text *InvalidText;
    sf::Font font;

    bool isInvalid;

    WhiteOctave *whiteOctaves[3];
    BlackOctave *blackOctaves[3];

public:
    Piano();
    ~Piano();

    void Play();
    void handleInput();
    void handleKeyboard();
    void display();
};

#endif
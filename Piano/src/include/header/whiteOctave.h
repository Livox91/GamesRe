#ifndef WHITE_OCTAVE_H_INCLUDED
#define WHITE_OCTAVE_H_INCLUDED

#include "whiteKey.h"

class WhiteOctave
{
private:
    WhiteKey *key[7];

public:
    WhiteOctave();
    WhiteOctave(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, const double frequency[]);
    ~WhiteOctave();

    void draw();
    void presskey(int keynum);
    void stopKeypress(int keynum);
};

#endif
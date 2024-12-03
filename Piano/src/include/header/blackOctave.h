#ifndef BLACK_OCTAVE_H_INCLUDED
#define BLACK_OCTAVE_H_INCLUDED

#include "blackKey.h"

class BlackOctave
{
private:
    BlackKey *keys[7];

public:
    BlackOctave();
    BlackOctave(sf::RenderWindow *renderWindow, sf::SoundBuffer *soundBuffer, int octaveNumber, const double frequency[]);
    ~BlackOctave();

    void draw();
    void presskey(int keynum);
    void stopKeypress(int keynum);
};

#endif
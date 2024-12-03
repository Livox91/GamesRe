#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

class Key
{
protected:
    sf::RenderWindow *window;
    sf::RectangleShape *rect;
    sf::Sound *sound;

    bool isPlaying;

public:
    Key();
    ~Key();
    void draw();
    void press();
    void stopPressing();
};
#endif
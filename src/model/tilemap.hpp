#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>

#include "animation.hpp"

class Tilemap {
   public:
    Tilemap();
    const float height_floor = 23.f;
    static const int W = 100;
    static const int H = 23;
    float i_banana = 0;
    const int q_banana = 17;
    float i_trophy = 0;
    const int q_trophy = 8;

    Animation ban(int q_frame, float step, std::string file);

    sf::RenderWindow window;
    sf::Texture terrain_tex;
    sf::Texture banana_tex;
    sf::Texture trophy_tex;
    sf::Texture background_tex;
    sf::Sprite ground;
    sf::Sprite ground_ora;
    sf::Sprite coin;
    sf::Sprite banana;
    sf::Sprite trophy;
    sf::Sprite background;
    sf::RectangleShape block;

    sf::Texture fire_tex;
    sf::Sprite fire;
    float i_fire = 0;
    const int q_fire = 4;

    static std::string map[H];

    void update();
    void draw(sf::RenderWindow *w);
};
#endif

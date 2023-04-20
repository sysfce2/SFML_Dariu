#include "animation.hpp"

#include "iostream"

using namespace std;

Animation::Animation() {
}
void Animation::init(int q_frame, float step, std::string file, sf::IntRect rect, bool circularSprite) {
    this->q_frame = q_frame;  // Needed 'this' cause same name param and prop.
    this->step = step;
    this->circularSprite = circularSprite;
    setTexture(file);
    setTextureRect(rect);
}
void Animation::anime(sf::IntRect rect) {
    this->setTextureRect(rect);
    this->next();
}

void Animation::next() {
    if (circularSprite) {
        // 0,1,2,3 then 0,1,2,3
        i_frame += step;
        if (i_frame >= q_frame) {
            i_frame = 0.f;
        }
    } else {
        // 0,1,2,3 then 3,2,1,0
        i_frame += step;
        if (i_frame >= (q_frame - step)) {
            i_frame--;
            step = step * -1;
        } else if (i_frame <= 0) {
            i_frame++;
            step = step * -1;
        }
        // cout << "Float: " << i_frame << "    Int: " << (int)i_frame << endl;
    }
}
void Animation::draw(float i, float j, sf::RenderWindow *w) {
    this->setPosition(i, j);
    w->draw(this->sprite);
}
void Animation::setTexture(std::string file) {
    texture.loadFromFile(file);
    sprite.setTexture(texture);
}
void Animation::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}
void Animation::setPosition(float i, float j) {
    sprite.setPosition(i, j);
}
int Animation::getFrame() {
    return (int)this->i_frame;
}
#include "background.h"

Background::Background(sf::RenderWindow* const window,
                       AssetManager* const manager)
    : BGSprite(manager->Background) {

  Window = window;
  BGSprite.setPosition(sf::Vector2f(0, 0));
}

void Background::Tick(const float deltatime) {
  BGSprite.setPosition(sf::Vector2f(0, Offset));
  Window->draw(BGSprite);
}

void Background::SetOffset(const float offset) { Offset = offset; }

#include "background.h"

Background::Background(sf::RenderWindow* const window,
                       AssetManager* const manager)
    : BGSprite(manager->Background) {
  Window = window;
  BGSprite.setPosition(sf::Vector2f(0, 0));
  for (int i = 0; i < 13 + rand() % 4; i++) {
    Clouds.push_back(Cloud(window, manager));
  }
}

void Background::Tick(const float deltatime) {
  BGSprite.setPosition(sf::Vector2f(0, Offset));
  Window->draw(BGSprite);
  for (Cloud& cloud : Clouds) {
    cloud.Tick(deltatime, Offset);
  }
}

void Background::SetOffset(const float offset) { Offset = offset; }

#include "background.h"

Background::Background(sf::RenderWindow* const window,
                       AssetManager* const manager)
    : BGSprite(manager->Background) {
  Window = window;
  BGSprite.setPosition(sf::Vector2f(0, 0));
  int decorCount = rand() % 6;
  for (int i = 0; i < 10 + decorCount; i++) {
    Clouds.push_back(Cloud(window, manager));
  }
  decorCount = rand() % 10;
  for (int i = 0; i < 10 + decorCount; i++) {
    Decorations.push_back(Decor(window, manager));
  }
}

void Background::Tick(const float deltatime) {
  BGSprite.setPosition(sf::Vector2f(0, Offset));
  Window->draw(BGSprite);
  for (Cloud& cloud : Clouds) {
    cloud.Tick(deltatime, Offset);
  }
  for (Decor& decor : Decorations) {
    decor.Tick(Offset);
  }
}

void Background::SetOffset(const float offset) { Offset = offset; }

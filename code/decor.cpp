#include "decor.h"

Decor::Decor(sf::RenderWindow* const window, AssetManager* const manager)
    : DecorSprite(manager->Background) {
  Window = window;
  Manager = manager;
  Spawn();
}

void Decor::Tick(const float offset) {
  DecorSprite.setPosition(sf::Vector2f(X, Y + offset));
  Window->draw(DecorSprite);
}

void Decor::Spawn() {
  Y = rand() % (Manager->UpDecorBorder - Manager->DownDecorBorder) +
      Manager->DownDecorBorder;
  X = rand() % (Manager->RightDecorBorder - Manager->LeftDecorBorder) +
      Manager->LeftDecorBorder;

  float scale = 0;
  if (rand() % 3 != 0) {
    Type = DecorTypes::Hedgehog;
  } else {
    Type = DecorTypes::Tree;
  }
  switch (Type) {
    case DecorTypes::Tree:
      DecorSprite.setTexture(Manager->Trees[rand() % Manager->Trees.size()]);
      scale = (Y - 300) / 600.0;
      break;
    case DecorTypes::Hedgehog:
      DecorSprite.setTexture(
          Manager->Hedgehogs[rand() % Manager->Hedgehogs.size()]);
      scale = (Y - 300) / 1000.0;
      break;
  }
  DecorSprite.setScale(sf::Vector2f(scale, scale));
}
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Explosion {
 public:
  Explosion(sf::RenderWindow* const window,
            AssetManager* const manager,
            const int location,
            const int charges, const bool hit);

  bool Tick(const float deltatime);

 private:
  sf::RenderWindow* Window;

  float LifeTime = 1;
  sf::Sprite ExplosionSprite;
  sf::Sound HitSound;
};
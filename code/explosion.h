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

  bool Tick(const float deltatime, const float shake);

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;

  float LifeTime = 1;
  int Location;
  sf::Sprite ExplosionSprite;
  sf::Sound HitSound;
};
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Explosion {
 public:
  Explosion(sf::RenderWindow* window, AssetManager* manager, int location,
            int charges, bool hit);

  sf::RenderWindow* Window;

  float LifeTime = 1;
  sf::Sprite ExplosionSprite;
  sf::Sound HitSound;

  bool Tick(float deltatime);
};
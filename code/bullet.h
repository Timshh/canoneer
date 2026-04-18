#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "enemy.h"

class Bullet {
 public:
  Bullet(sf::RenderWindow* const window, Enemy* const target,
         AssetManager* const manager, const int coord, const int charges,
         const int type);

  int ShotCharges, ShotCoord, WindX, WindY, Type;
  float FlyTime;

  bool Tick(const float deltatime);

 private:
  Enemy* Target;
  AssetManager* Manager;
  sf::RenderWindow* Window;

  float Lifetime = 0;
  sf::Sprite BulletSprite;
};
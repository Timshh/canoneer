#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "enemy.h"

class Bullet {
 public:
  Bullet(sf::RenderWindow* window, Enemy* target, AssetManager* manager,
         int coord, int charges,
         int flyTime, int type);

  Enemy* Target;
  AssetManager* Manager;
  sf::RenderWindow* Window;
  
  int ShotCharges, ShotCoord, WindX, WindY, Type;
  float FlyTime, Lifetime = 0;
  sf::Sprite BulletSprite;

  bool Tick(float deltatime);
};
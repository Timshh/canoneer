#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "enemy.h"

class Bullet {
 public:
  Bullet(sf::RenderWindow* window, Enemy* target, AssetManager* manager,
         int coord, int charges,
         int flyTime);

  Enemy* Target;
  AssetManager* Manager;
  sf::RenderWindow* Window;
  
  int ShotCharges, ShotCoord;
  float FlyTime;
  //sf::Sprite BulletSprite;

  bool Tick(float deltatime);
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "enemy.h"

class Bullet {
 public:
  Bullet(sf::RenderWindow* window, Enemy* target, int coord, int charges, int flyTime);
  Enemy* Target;
  sf::RenderWindow* Window;
  int ShotCharges, ShotCoord;
  float FlyTime;
  sf::SoundBuffer* HitBuffer;
  sf::Sound* HitSound;
  sf::Texture BulletTexture;
  sf::Sprite *BulletSprite;

  bool Tick(float deltatime);
};
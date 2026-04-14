#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

class Canon {
 public:
  Canon(sf::RenderWindow* window, AssetManager* manager);

  sf::RenderWindow* Window;
  AssetManager* Manager;
  Bullet* Shot = nullptr;
  Explosion* Explode = nullptr;
  Enemy* Target;

  int AimCoord = 0, Charges = 0;
  bool RightPressed = false, LeftPressed = false, UpPressed = false,
       DownPressed = false, LmbPressed = false, RmbPressed = false;
  sf::Sound ShotSound;
  sf::Text TimerText, ChargesText;
  sf::Sprite AimSprite, CanonSprite;

  void DrawCanon(float deltatime);
  void Tick(float deltatime, Enemy* target);
};
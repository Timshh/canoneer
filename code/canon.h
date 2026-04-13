#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "bullet.h"
#include "enemy.h"

class Canon {
 public:
  Canon(sf::RenderWindow* window, AssetManager* manager);
  sf::RenderWindow* Window;
  AssetManager* Manager;
  int AimCoord = 0, Charges = 0;
  bool RightPressed = false, LeftPressed = false, UpPressed = false,
       DownPressed = false, LmbPressed = false, RmbPressed = false;
  Bullet* Shot = 0;
  Enemy* Target;
  sf::Sound ShotSound;
  sf::Font* Font;
  sf::Text TimerText, ChargesText;
  sf::Sprite AimSprite, CanonSprite;

  void DrawCanon();
  void Tick(float deltatime, Enemy* target);
};
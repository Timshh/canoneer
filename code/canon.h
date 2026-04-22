#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

class Canon {
 public:
  Canon(sf::RenderWindow* const window, AssetManager* const manager);

  void Tick(const float deltatime, Enemy* const target);
  void SubRender();
  void TickInput();
  void Reset();
  float GetOffset(const float deltatime);

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;
  std::unique_ptr<Bullet> Shot = nullptr;
  std::unique_ptr<Explosion> Explode = nullptr;
  Enemy* Target;

  int AimCoord = 0, Charges = 0, Type = 0, ShakeFloor = 0;
  const int ShakeMult = 50;
  float FireTime = 0, HitTime = 0, Shake = 0;
  const float FireTimeMult = 0.2;
  bool RightPressed = false, LeftPressed = false, UpPressed = false,
       DownPressed = false, ZPressed = false, XPressed = false,
       CPressed = false;
  sf::Sound ShotSound;
  sf::Text TimerText, ChargesText, TypeText;
  sf::Sprite AimSprite, CanonSprite, ReadySprite, HitSprite;
};
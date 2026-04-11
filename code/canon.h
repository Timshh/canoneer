#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "bullet.h"
#include "enemy.h"

class Canon {
 public:
  Canon(sf::RenderWindow* window, sf::Font *font);
  sf::RenderWindow* Window;
  int AimCoord = 0, Charges = 0;
  bool RightPressed = false, LeftPressed = false, UpPressed = false,
       DownPressed = false, LmbPressed = false, RmbPressed = false;
  Bullet* Shot = 0;
  Enemy* Target;
  sf::SoundBuffer* ShotBuffer = nullptr;
  sf::Sound* ShotSound = nullptr;
  sf::Font* Font;
  sf::Text TimerText, ChargesText;
  sf::Texture Aim, CanonTexture, Ready, NonReady;
  sf::Sprite AimSprite, CanonSprite;

  void DrawCanon();
  void Tick(float deltatime, Enemy* target);
};
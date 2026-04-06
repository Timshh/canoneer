#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "enemy.h"
#include "bullet.h"

class Canon {
 public:
  Canon(sf::RenderWindow* window, std::string font);
  sf::RenderWindow* Window;
  int AimCoord = 0, Charges = 0;
  bool RightPressed = 0, LeftPressed = 0, UpPressed = 0, DownPressed = 0, LmbPressed = 0, RmbPressed = 0;
  Bullet* Shot = 0;
  Enemy* Target;
  sf::SoundBuffer* ShotBuffer;
  sf::Sound* ShotSound;
  sf::Font Font;
  sf::Text TimerText = sf::Text(Font, "", 50);
  sf::Text ChargesText = sf::Text(Font, "", 50);
  sf::Texture Aim, CanonTexture, Ready, NonReady;
  sf::Sprite *AimSprite, *CanonSprite;

  void DrawCanon();
  void Tick(float deltatime, Enemy* target);
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Canon {
 public:
  Canon(sf::RenderWindow* window, std::string font);

  sf::RenderWindow* Window;
  int ShotCharges, ShotCoord, AimCoord = 0, Charges = 0;
  float FlyTime = 0;
  bool RightPressed = 0, LeftPressed = 0, UpPressed = 0, DownPressed = 0, Shot = 0, LmbPressed = 0, RmbPressed = 0;
  sf::SoundBuffer* ShotBuffer;
  sf::Sound* ShotSound;
  sf::Font Font;
  sf::Text TimerText = sf::Text(Font, "", 50);
  sf::Text ChargesText = sf::Text(Font, "", 50);
  sf::Texture Aim, CanonTexture, Ready, NonReady;
  sf::Sprite *AimSprite, *CanonSprite;

  void DrawCanon();
  bool Tick(float deltatime);
};
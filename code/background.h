#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "assetManager.h"

class Background {
 public:
  Background(sf::RenderWindow* const window, AssetManager* const manager);

  

  void Tick(const float deltatime);
  void SetOffset(const float offset);

 private:
  sf::RenderWindow* Window;

  sf::Sprite BGSprite;
  float Offset;
};
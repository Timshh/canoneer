#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "assetManager.h"
#include "cloud.h"
#include "decor.h"

class Background {
 public:
  Background(sf::RenderWindow* const window, AssetManager* const manager);

  void Tick(const float deltatime);
  void SetOffset(const float offset);
  void Reset();

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;

  std::vector<Cloud> Clouds;
  std::vector<Decor> Decorations;
  sf::Sprite BGSprite;
  float Offset;
};
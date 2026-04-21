#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Cloud {
 public:
  Cloud(sf::RenderWindow* const window,
            AssetManager* const manager);

  void Tick(const float deltatime, const float shake);

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;

  void Spawn();
  float X, Y, Speed, Step = 0;
  
  sf::Sprite CloudSprite;

};
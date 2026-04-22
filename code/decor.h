#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"

enum class DecorTypes { Hedgehog, Tree };

class Decor {
 public:
  Decor(sf::RenderWindow* const window,
            AssetManager* const manager);

  void Tick(const float shake);

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;

  DecorTypes Type;
  void Spawn();
  float X, Y;
  
  sf::Sprite DecorSprite;

};
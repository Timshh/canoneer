#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Enemy {
 public:
  Enemy(sf::RenderWindow* const window, AssetManager* const manager,
        const int coord, const int windX,
        const int windY, const int distance, const int type);

  sf::RenderWindow* Window;

  int WindX, WindY, Distance, Coord, Type;
  bool Alive = true;

  bool Hit(const int coord, const int distance, const int type);
  bool Tick(const float deltatime);

 private:
  sf::Text WindXText, WindYText, XText, YText, DistanceText, TypeText;
};
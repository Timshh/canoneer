#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Enemy {
 public:
  Enemy(sf::RenderWindow* window, AssetManager* manager, int coord, int windX,
        int windY, int distance);

  sf::RenderWindow* Window;

  int WindX, WindY, Distance, Coord;
  bool Alive = true;
  sf::Text WindXText, WindYText, XText, YText, DistanceText;

  bool Hit(int coord, int distance);
  bool Tick(float deltatime);
};
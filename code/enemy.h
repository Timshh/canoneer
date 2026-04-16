#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Enemy {
 public:
  Enemy(sf::RenderWindow* window, AssetManager* manager, int coord, int windX,
        int windY, int distance, int type);

  sf::RenderWindow* Window;

  int WindX, WindY, Distance, Coord, Type;
  bool Alive = true;
  sf::Text WindXText, WindYText, XText, YText, DistanceText, TypeText;

  bool Hit(int coord, int distance, int type);
  bool Tick(float deltatime);
};
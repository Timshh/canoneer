#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
 public:
  Enemy(sf::RenderWindow* window, sf::Font* font, int coord, int windX,
        int windY, int distance);
  sf::RenderWindow* Window;
  int WindX, WindY, Distance, Coord;
  bool Alive = true;
  sf::Font* Font;
  sf::Text WindXText, WindYText, XText, YText, DistanceText;

  bool Hit(int coord, int distance);
  bool Tick(float deltatime);
};
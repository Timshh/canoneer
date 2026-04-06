#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
 public:
  Enemy(sf::RenderWindow* window, std::string font, int coord, int windX,
        int windY, int distance);
  sf::RenderWindow* Window;
  int WindX, WindY, Distance, Coord;
  bool Alive = 1;
  sf::Font Font;
  sf::Text WindXText = sf::Text(Font, "", 50);
  sf::Text WindYText = sf::Text(Font, "", 50);
  sf::Text XText = sf::Text(Font, "", 50);
  sf::Text YText = sf::Text(Font, "", 50);
  sf::Text DistanceText = sf::Text(Font, "", 50);

  bool Hit(int coord, int distance);
  bool Tick(float deltatime);
};
#include "enemy.h"

Enemy::Enemy(sf::RenderWindow* window, std::string font, int coord, int windX,
             int windY,
             int distance) {
  Window = window;
  Coord = coord;
  WindX = windX;
  WindY = windY;
  Distance = distance;
  Font.openFromFile(font);
  WindYText.setFillColor(sf::Color::Black);
  DistanceText.setFillColor(sf::Color::Black);
  WindXText.setFillColor(sf::Color::Black);
  XText.setFillColor(sf::Color::Black);
  YText.setFillColor(sf::Color::Black);
  WindXText.setPosition(sf::Vector2(1734.0f, 322.0f));
  WindYText.setPosition(sf::Vector2(1734.0f, 414.0f));
  XText.setPosition(sf::Vector2(1734.0f, 506.0f));
  YText.setPosition(sf::Vector2(1734.0f, 598.0f));
  DistanceText.setPosition(sf::Vector2(1734.0f, 690.0f));
}



bool Enemy::Hit(int coord, int distance) {
  if (coord == Coord - WindX * Distance - WindY * 9 * Distance and
      Distance == distance) {
    Alive = 0;
    return 1;
  }
  return 0;
}

bool Enemy::Tick(float deltatime) {
  DistanceText.setString(std::to_string(Distance));
  Window->draw(DistanceText);

  WindXText.setString(std::to_string((int)WindX));
  Window->draw(WindXText);

  WindYText.setString(std::to_string((int)WindY));
  Window->draw(WindYText);

  XText.setString(std::to_string(Coord % 9 + 1));
  Window->draw(XText);

  YText.setString(std::to_string((int)(Coord / 9) + 1));
  Window->draw(YText);
  if (!Alive) {  
    return 1;
  }
  return 0;
}
#include "enemy.h"

Enemy::Enemy(sf::RenderWindow* window, AssetManager* manager, int coord,
             int windX,
             int windY, int distance)
    : Font(manager->GetFont()),
      WindXText(*Font, "", 50),
      DistanceText(*Font, "", 50),
      WindYText(*Font, "", 50),
      XText(*Font, "", 50),
      YText(*Font, "", 50) {
  Window = window;
  Coord = coord;
  WindX = windX;
  WindY = windY;
  Distance = distance;
  WindYText.setFillColor(sf::Color::Black);
  DistanceText.setFillColor(sf::Color::Black);
  WindXText.setFillColor(sf::Color::Black);
  XText.setFillColor(sf::Color::Black);
  YText.setFillColor(sf::Color::Black);
  WindXText.setPosition(sf::Vector2f(1734.0, 322.0));
  WindYText.setPosition(sf::Vector2f(1734.0, 414.0));
  XText.setPosition(sf::Vector2f(1734.0, 506.0));
  YText.setPosition(sf::Vector2f(1734.0, 598.0));
  DistanceText.setPosition(sf::Vector2f(1734.0, 690.0));
}

bool Enemy::Hit(int coord, int distance) {
  if (coord == Coord - WindX * Distance - WindY * 9 * Distance and
      Distance == distance) {
    Alive = false;
    return 1;
  }
  return 0;
}

bool Enemy::Tick(float deltatime) {
  DistanceText.setString(std::to_string(Distance));
  Window->draw(DistanceText);

  WindXText.setString(std::to_string(static_cast<int>(WindX)));
  Window->draw(WindXText);

  WindYText.setString(std::to_string(static_cast<int>(WindY)));
  Window->draw(WindYText);

  XText.setString(std::to_string(Coord % 9 + 1));
  Window->draw(XText);

  YText.setString(std::to_string(static_cast<int>((Coord / 9) + 1)));
  Window->draw(YText);
  if (!Alive) {
    return 1;
  }
  return 0;
}
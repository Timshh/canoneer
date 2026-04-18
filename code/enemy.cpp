#include "enemy.h"

Enemy::Enemy(sf::RenderWindow* const window, AssetManager* const manager,
             const int coord, const int windX, const int windY,
             const int distance, const int type)
    : WindXText(manager->Font, "", 50),
      DistanceText(manager->Font, "", 50),
      WindYText(manager->Font, "", 50),
      XText(manager->Font, "", 50),
      YText(manager->Font, "", 50),
      TypeText(manager->Font, "", 50) {
  Window = window;
  Coord = coord;
  WindX = windX;
  WindY = windY;
  Distance = distance;
  Type = type;
  switch (Type) {
    case 0:
      TypeText.setString("Sol");
      break;
    case 1:
      TypeText.setString("Hev");
      break;
    case 2:
      TypeText.setString("Air");
      break;
  }

  TypeText.setFillColor(sf::Color::Black);
  XText.setFillColor(sf::Color::Black);
  YText.setFillColor(sf::Color::Black);
  DistanceText.setFillColor(sf::Color::Black);
  WindXText.setFillColor(sf::Color::Black);
  WindYText.setFillColor(sf::Color::Black);

  TypeText.setPosition(sf::Vector2f(1734.0, 230.0));
  XText.setPosition(sf::Vector2f(1734.0, 322.0));
  YText.setPosition(sf::Vector2f(1734.0, 414.0));
  DistanceText.setPosition(sf::Vector2f(1734.0, 506.0));
  WindXText.setPosition(sf::Vector2f(1734.0, 598.0));
  WindYText.setPosition(sf::Vector2f(1734.0, 690.0));
}

bool Enemy::Hit(const int coord, const int distance, const int type) {
  if (coord == Coord - WindX * Distance - WindY * 9 * Distance &&
      Distance == distance && type == Type) {
    Alive = false;
    return true;
  }
  return false;
}

bool Enemy::Tick(const float deltatime) {
  // Texts
  DistanceText.setString(std::to_string(Distance));
  WindXText.setString(std::to_string(static_cast<int>(WindX)));
  WindYText.setString(std::to_string(static_cast<int>(WindY)));
  XText.setString(std::to_string(Coord % 9 + 1));
  YText.setString(std::to_string(static_cast<int>((Coord / 9) + 1)));
  // Draw
  Window->draw(DistanceText);
  Window->draw(WindXText);
  Window->draw(WindYText);
  Window->draw(XText);
  Window->draw(YText);
  Window->draw(TypeText);

  if (!Alive) {
    return 1;
  }
  return 0;
}
#include "enemy.h"

Enemy::Enemy(sf::RenderWindow* const window, AssetManager* const manager,
             const int coord, const int windX, const int windY,
             const int distance, const int type)
    : WindXText(manager->Font, "", manager->TextSizeMid),
      DistanceText(manager->Font, "", manager->TextSizeMid),
      WindYText(manager->Font, "", manager->TextSizeMid),
      XText(manager->Font, "", manager->TextSizeMid),
      YText(manager->Font, "", manager->TextSizeMid),
      TypeText(manager->Font, "", manager->TextSizeMid) {
  Window = window;
  Coord = coord;
  WindX = windX;
  WindY = windY;
  Distance = distance;
  Type = type;
  Columns = manager->Columns;
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

  TypeText.setFillColor(manager->MainColor);
  XText.setFillColor(manager->MainColor);
  YText.setFillColor(manager->MainColor);
  DistanceText.setFillColor(manager->MainColor);
  WindXText.setFillColor(manager->MainColor);
  WindYText.setFillColor(manager->MainColor);

  TypeText.setPosition(sf::Vector2f(manager->RightHUDColumn, manager->HUDRow1));
  XText.setPosition(sf::Vector2f(manager->RightHUDColumn, manager->HUDRow2));
  YText.setPosition(sf::Vector2f(manager->RightHUDColumn, manager->HUDRow3));
  DistanceText.setPosition(
      sf::Vector2f(manager->RightHUDColumn, manager->HUDRow4));
  WindXText.setPosition(
      sf::Vector2f(manager->RightHUDColumn, manager->HUDRow5));
  WindYText.setPosition(
      sf::Vector2f(manager->RightHUDColumn, manager->HUDRow6));
}

bool Enemy::Hit(const int coord, const int distance, const int type) {
  if (coord == Coord - WindX * Distance - WindY * Columns * Distance &&
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
  XText.setString(std::to_string(Coord % Columns + 1));
  YText.setString(std::to_string(static_cast<int>((Coord / Columns) + 1)));
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
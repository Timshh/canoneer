#include "bullet.h"

Bullet::Bullet(sf::RenderWindow* const window, Enemy* const target,
               AssetManager* const manager, const int coord, const int charges,
               const int type)
    : BulletSprite(manager->Bullet) {
  Window = window;
  Manager = manager;
  Target = target;
  WindX = target->WindX;
  WindY = target->WindY;
  ShotCoord = coord;
  ShotCharges = charges;
  FlyTime = charges * Manager->TimeMult;
  Type = type;
}

bool Bullet::Tick(const float deltatime, const float offset) {
  FlyTime -= deltatime;
  Lifetime += deltatime;
  float Delta = std::floor(Lifetime);
  float AimX = ShotCoord % Manager->Columns;
  float AimY = static_cast<int>(ShotCoord / Manager->Columns);
  BulletSprite.setPosition(sf::Vector2f(
      Manager->GridStartX + Manager->CellSize * AimX + 4.6 * Delta +
          Delta / 3 * WindX * Manager->CellSize,
      Manager->GridStartY + Manager->CellSize * AimY + 4.6 * Delta +
          Delta / 3 * WindY * Manager->CellSize + offset));
  BulletSprite.setScale(sf::Vector2f(1 - Delta * 0.1, 1 - Delta * 0.1));
  Window->draw(BulletSprite);
  if (FlyTime <= 0) {
    Target->Hit(ShotCoord, ShotCharges, Type);
    return 1;
  }
  return 0;
}
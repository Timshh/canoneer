#include "bullet.h"

Bullet::Bullet(sf::RenderWindow* window, Enemy* target, AssetManager* manager,
               int coord, int charges, int flyTime, int type)
    : BulletSprite(manager->Bullet) {
  Window = window;
  Manager = manager;
  Target = target;
  WindX = target->WindX;
  WindY = target->WindY;
  ShotCoord = coord;
  ShotCharges = charges;
  FlyTime = flyTime;
  Type = type;
}

bool Bullet::Tick(float deltatime) {
  FlyTime -= deltatime;
  Lifetime += deltatime;
  float Delta = std::floor(Lifetime);
  float AimX = ShotCoord % 9;
  float AimY = static_cast<int>(ShotCoord / 9);
  BulletSprite.setPosition(
      sf::Vector2f(546 + 92 * AimX + 4.6 * Delta + Delta / 3 * WindX * 92,
                   218 + 92 * AimY + 4.6 * Delta + Delta / 3 * WindY * 92));
  BulletSprite.setScale(sf::Vector2f(1 - Delta * 0.1, 1 - Delta * 0.1));
  Window->draw(BulletSprite);
  if (FlyTime <= 0) {
    Target->Hit(ShotCoord, ShotCharges, Type);
    return 1;
  }
  return 0;
}
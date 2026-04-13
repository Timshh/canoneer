#include "bullet.h"

Bullet::Bullet(sf::RenderWindow* window, Enemy* target, AssetManager* manager,
               int coord, int charges, int flyTime) {
  Window = window;
  Manager = manager;
  Target = target;
  ShotCoord = coord;
  ShotCharges = charges;
  FlyTime = flyTime;
}

bool Bullet::Tick(float deltatime) {
  FlyTime -= deltatime;
  if (FlyTime <= 0) {
    Target->Hit(ShotCoord, ShotCharges);
    /*if (Target->Hit(ShotCoord, ShotCharges)) {
      HitSound.setBuffer(Manager->Hit);
      HitSound.play();
    } else {
      HitSound.setBuffer(Manager->Miss);
      HitSound.play();
    }*/
    // Will be replaced later with explosion
    return 1;
  }
  return 0;
}
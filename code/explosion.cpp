#include "explosion.h"

Explosion::Explosion(sf::RenderWindow* const window,
                     AssetManager* const manager, const int location,
                     const int charges, const bool hit)
    : ExplosionSprite(manager->ExplosionNear), HitSound(manager->Hit) {
  Window = window;
  Manager = manager;
  Location = location;
  if (hit) {
    HitSound.setBuffer(manager->Hit);
  } else {
    HitSound.setBuffer(manager->Miss);
  }
  switch (charges) {
    case 1:
      ExplosionSprite.setTexture(manager->ExplosionNear);
      break;
    case 2:
      ExplosionSprite.setTexture(manager->ExplosionMid);
      break;
    case 3:
      ExplosionSprite.setTexture(manager->ExplosionFar);
      break;
  }
  HitSound.play();
}

bool Explosion::Tick(const float deltatime, const float offset) {
  LifeTime -= deltatime;
  float AimX = Location % Manager->Columns;
  float AimY = Location / Manager->Columns;
  ExplosionSprite.setPosition(
      sf::Vector2f(Manager->GridStartX + Manager->CellSize * AimX,
                   Manager->GridStartY + Manager->CellSize * AimY + offset));
  if (LifeTime <= 0) {  
    return 1;
  }
  Window->draw(ExplosionSprite);
  return 0;
}
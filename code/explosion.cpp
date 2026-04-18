#include "explosion.h"

Explosion::Explosion(sf::RenderWindow* const window,
                     AssetManager* const manager, const int location,
                     const int charges, const bool hit)
    : ExplosionSprite(manager->ExplosionNear), HitSound(manager->Hit) {
  Window = window;
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
  float AimX = location % 9;
  float AimY = static_cast<int>(location / 9);
  ExplosionSprite.setPosition(sf::Vector2f(546 + 92 * AimX, 218 + 92 * AimY));
  HitSound.play();
}

bool Explosion::Tick(const float deltatime) {
  LifeTime -= deltatime;
  if (LifeTime <= 0) {  
    return 1;
  }
  Window->draw(ExplosionSprite);
  return 0;
}
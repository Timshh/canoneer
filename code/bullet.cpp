#include "bullet.h"

Bullet::Bullet(sf::RenderWindow* window, Enemy* target, int coord, int charges,
               int flyTime) {
  Window = window;
  Target = target;
  ShotCoord = coord;
  ShotCharges = charges;
  FlyTime = flyTime;
}

bool Bullet::Tick(float deltatime) {
  FlyTime -= deltatime;
  if (FlyTime <= 0) {
    if (Target->Hit(ShotCoord, ShotCharges)) {
      HitBuffer = new sf::SoundBuffer();
      HitBuffer->loadFromFile("data/Hit.wav");
      HitSound = new sf::Sound(*HitBuffer);
      HitSound->play();
    } else {
      HitBuffer = new sf::SoundBuffer();
      HitBuffer->loadFromFile("data/Miss.wav");
      HitSound = new sf::Sound(*HitBuffer);
      HitSound->play();
    }
    return 1;
  }
  return 0;
}
#include "cloud.h"

Cloud::Cloud(sf::RenderWindow* const window, AssetManager* const manager)
    : CloudSprite(manager->Clouds[0]) {
  Window = window;
  Manager = manager;
  Spawn();
  X = rand() % (Manager->RightCloudBorder - Manager->LeftCloudBorder) +
      Manager->LeftCloudBorder;
}

void Cloud::Tick(const float deltatime, const float offset) {
  Step += deltatime;
  if (Step >= 1) {
    X += Speed * Step;
    Step = 0;
    if (X > Manager->RightCloudBorder || X < Manager->LeftCloudBorder) {
      Spawn();
    }
  }
  CloudSprite.setPosition(sf::Vector2f(X, Y + offset));
  Window->draw(CloudSprite);
}

void Cloud::Spawn() {
  CloudSprite.setTexture(Manager->Clouds[rand() % Manager->Clouds.size()]);
  float scale = (rand() % 8 + 2) / 10.0;
  CloudSprite.setScale(sf::Vector2f(scale, scale));
  Y = rand() % (Manager->UpCloudBorder - Manager->DownCloudBorder) +
      Manager->DownCloudBorder;
  int mult;
  if (rand() % 2 == 0) {
    mult = 1;
    X = Manager->LeftCloudBorder;
  } else {
    mult = -1;
    X = Manager->RightCloudBorder;
  }
  Speed = (rand() % 20 + 1) * mult * 0.1;
}
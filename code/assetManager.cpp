#include "assetManager.h"

AssetManager::AssetManager() {
  bool Opened = Font.openFromFile("data/Tiny5.ttf") &&
                End.loadFromFile("data/Ending.wav") &&
                Hit.loadFromFile("data/Hit.wav") &&
                Miss.loadFromFile("data/Miss.wav") &&
                ShotWeak.loadFromFile("data/FireWeak.wav") &&
                ShotMid.loadFromFile("data/FireMid.wav") &&
                ShotHeavy.loadFromFile("data/FireHeavy.wav") &&
                Background.loadFromFile("data/BG.png") &&
                UI.loadFromFile("data/ArtUI.png") &&
                Cell.loadFromFile("data/Cell.png") &&
                Aim.loadFromFile("data/Aim.png") &&
                Canon.loadFromFile("data/Canon.png") &&
                CanonFire.loadFromFile("data/CanonFire.png") &&
                Ready.loadFromFile("data/Ready.png") &&
                NonReady.loadFromFile("data/NonReady.png") &&
                ExplosionFar.loadFromFile("data/ExplosionFar.png") &&
                ExplosionMid.loadFromFile("data/ExplosionMid.png") &&
                ExplosionNear.loadFromFile("data/ExplosionNear.png") &&
                Bullet.loadFromFile("data/Bullet.png");
  if (!Opened) {
    throw std::runtime_error("Failed to load data");
  }
}
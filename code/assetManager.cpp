#include "assetManager.h"

AssetManager::AssetManager(sf::RenderWindow* window) {
  bool Opened = Font.openFromFile("data/Tiny5.ttf") and
                End.loadFromFile("data/Ending.wav") and
                Hit.loadFromFile("data/Hit.wav") and
                Miss.loadFromFile("data/Miss.wav") and
                ShotWeak.loadFromFile("data/FireWeak.wav") and
                ShotMid.loadFromFile("data/FireMid.wav") and
                ShotHeavy.loadFromFile("data/FireHeavy.wav") and
                Background.loadFromFile("data/BG.png") and
                UI.loadFromFile("data/ArtUI.png") and
                Cell.loadFromFile("data/Cell.png") and
                Aim.loadFromFile("data/Aim.png") and
                Canon.loadFromFile("data/Canon.png") and
                CanonFire.loadFromFile("data/CanonFire.png") and
                Ready.loadFromFile("data/Ready.png") and
                NonReady.loadFromFile("data/NonReady.png") and
                ExplosionFar.loadFromFile("data/ExplosionFar.png") and
                ExplosionMid.loadFromFile("data/ExplosionMid.png") and
                ExplosionNear.loadFromFile("data/ExplosionNear.png") and
                Bullet.loadFromFile("data/Bullet.png");
  if (!Opened) {
    window->close();
  }
}
#include "assetManager.h"

AssetManager::AssetManager() {
  sf::Texture loaded;
  bool Opened = true;
  Opened &= OpenResource(Font, "data/Tiny5.ttf");

  Opened &= LoadResource(Background, "data/BG.png");
  Opened &= LoadResource(loaded, "data/Cloud1.png");
  Clouds.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Cloud2.png");
  Clouds.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Cloud3.png");
  Clouds.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Cloud4.png");
  Clouds.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Cloud5.png");
  Clouds.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Hedgehog1.png");
  Hedgehogs.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Hedgehog2.png");
  Hedgehogs.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Hedgehog3.png");
  Hedgehogs.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Tree1.png");
  Trees.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Tree2.png");
  Trees.push_back(loaded);
  Opened &= LoadResource(loaded, "data/Tree3.png");
  Trees.push_back(loaded);

  Opened &= LoadResource(UI, "data/ArtUI.png");
  Opened &= LoadResource(Cell, "data/Cell.png");
  Opened &= LoadResource(Barrier, "data/Barrier.png");

  Opened &= LoadResource(Aim, "data/Aim.png");
  Opened &= LoadResource(Ready, "data/Ready.png");
  Opened &= LoadResource(NonReady, "data/NonReady.png");

  Opened &= LoadResource(Canon, "data/Canon.png");
  Opened &= LoadResource(CanonFire, "data/CanonFire.png");

  Opened &= LoadResource(Bullet, "data/Bullet.png");
  Opened &= LoadResource(ExplosionFar, "data/ExplosionFar.png");
  Opened &= LoadResource(ExplosionMid, "data/ExplosionMid.png");
  Opened &= LoadResource(ExplosionNear, "data/ExplosionNear.png");

  Opened &= LoadResource(Start, "data/Start.wav");
  Opened &= LoadResource(End, "data/Ending.wav");
  Opened &= LoadResource(Hit, "data/Hit.wav");
  Opened &= LoadResource(Miss, "data/Miss.wav");
  Opened &= LoadResource(ShotWeak, "data/FireWeak.wav");
  Opened &= LoadResource(ShotMid, "data/FireMid.wav");
  Opened &= LoadResource(ShotHeavy, "data/FireHeavy.wav");

  if (!Opened) {
    throw std::runtime_error("Failed to load data");
  }
}

bool AssetManager::LoadResource(auto& resource, const std::string& path) {
  if (!resource.loadFromFile(path)) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  return true;
}

bool AssetManager::OpenResource(auto& resource, const std::string& path) {
  if (!resource.openFromFile(path)) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  return true;
}

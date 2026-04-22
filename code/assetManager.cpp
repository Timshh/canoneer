#include "assetManager.h"

AssetManager::AssetManager() {
  auto load = [](auto& resource, const std::string& path) {
    if (!resource.loadFromFile(path)) {
      std::cerr << "Failed to load: " << path << "\n";
      return false;
    }
    return true;
  };

  auto open = [](auto& resource, const std::string& path) {
    if (!resource.openFromFile(path)) {
      std::cerr << "Failed to load: " << path << "\n";
      return false;
    }
    return true;
  };
  sf::Texture loaded;
  bool opened = true;
  opened &= open(Font, "data/Tiny5.ttf");

  opened &= load(Background, "data/BG.png");
  opened &= load(loaded, "data/Cloud1.png");
  Clouds.push_back(loaded);
  opened &= load(loaded, "data/Cloud2.png");
  Clouds.push_back(loaded);
  opened &= load(loaded, "data/Cloud3.png");
  Clouds.push_back(loaded);
  opened &= load(loaded, "data/Cloud4.png");
  Clouds.push_back(loaded);
  opened &= load(loaded, "data/Cloud5.png");
  Clouds.push_back(loaded);
  opened &= load(loaded, "data/Hedgehog1.png");
  Hedgehogs.push_back(loaded);
  opened &= load(loaded, "data/Hedgehog2.png");
  Hedgehogs.push_back(loaded);
  opened &= load(loaded, "data/Hedgehog3.png");
  Hedgehogs.push_back(loaded);
  opened &= load(loaded, "data/Tree1.png");
  Trees.push_back(loaded);
  opened &= load(loaded, "data/Tree2.png");
  Trees.push_back(loaded);
  opened &= load(loaded, "data/Tree3.png");
  Trees.push_back(loaded);

  opened &= load(UI, "data/ArtUI.png");
  opened &= load(Cell, "data/Cell.png");
  opened &= load(Barrier, "data/Barrier.png");

  opened &= load(Aim, "data/Aim.png");
  opened &= load(Ready, "data/Ready.png");
  opened &= load(NonReady, "data/NonReady.png");

  opened &= load(Canon, "data/Canon.png");
  opened &= load(CanonFire, "data/CanonFire.png");

  opened &= load(Bullet, "data/Bullet.png");
  opened &= load(ExplosionFar, "data/ExplosionFar.png");
  opened &= load(ExplosionMid, "data/ExplosionMid.png");
  opened &= load(ExplosionNear, "data/ExplosionNear.png");

  opened &= load(Start, "data/Start.wav");
  opened &= load(End, "data/Ending.wav");
  opened &= load(Hit, "data/Hit.wav");
  opened &= load(Miss, "data/Miss.wav");
  opened &= load(ShotWeak, "data/FireWeak.wav");
  opened &= load(ShotMid, "data/FireMid.wav");
  opened &= load(ShotHeavy, "data/FireHeavy.wav");

  if (!opened) {
    throw std::runtime_error("Failed to load data");
  }
}
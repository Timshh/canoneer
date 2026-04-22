#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "canon.h"
#include "enemy.h"
#include "score.h"
#include "background.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* const window,
           AssetManager* const manager);

  void Tick();

 private:
  bool HPressed = false, TutorialHidden = false;
  float BarrierStartPosition = -650, BarrierPosition = 0, BarrierDelta = 170;

  AssetManager* Manager;
  std::unique_ptr<Score> Scores;
  std::unique_ptr<Canon> Weapon;
  Background BG;

  Enemy* Target = nullptr;
  sf::RenderWindow* Window;
  sf::Clock Time;
  sf::Text TutorialText, TutorialText2, TutorialText3, HintText;
  sf::Sprite BarrierSprite, UISprite;
  std::vector<sf::Sprite> Cells = {};

  Enemy* NewTarget();
};
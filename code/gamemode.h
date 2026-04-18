#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "canon.h"
#include "enemy.h"
#include "score.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* const window,
           AssetManager* const manager);

  void Tick();

 private:
  bool HPressed = false, TutorialHidden = false;

  AssetManager* Manager;
  std::unique_ptr<Score> Scores;
  std::unique_ptr<Canon> Weapon;

  Enemy* Target;
  sf::RenderWindow* Window;
  sf::Clock Time;
  sf::Text TutorialText, TutorialText2, TutorialText3, TypeText;
  sf::Sprite BGSprite, UISprite;
  std::vector<sf::Sprite> Cells = {};

  Enemy* NewTarget();
};
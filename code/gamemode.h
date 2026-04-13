#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "canon.h"
#include "enemy.h"
#include "score.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window, AssetManager* manager);
  AssetManager* Manager;
  Score* Scores;
  Canon* Weapon;
  sf::RenderWindow* Window;
  bool HPressed = false, TutorialHidden = false;
  Enemy* Target;
  sf::Clock Time;
  sf::Font* Font;
  sf::Text TutorialText;
  sf::Text TutorialText2;
  sf::Text TutorialText3;
  sf::Sprite BGSprite, UISprite;
  std::vector<sf::Sprite> Cells = {};

  void Tick();
  Enemy* NewTarget();
};
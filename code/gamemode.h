#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "canon.h"
#include "enemy.h"
#include "score.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  Score* Scores;
  Canon* Weapon;
  sf::RenderWindow* Window;
  bool HPressed = false, TutorialHidden = false;
  const std::string FontPath = "data/Tiny5.ttf";
  Enemy* Target;
  sf::Clock Time;
  sf::Font Font;
  sf::Text TutorialText =
      sf::Text(Font,
               "Tutorial: arrows to aim, rmb to charge, lmb to fire. Esc to "
               "exit. Aim at enemy coordinates, load charges",
               40);
  sf::Text TutorialText2 =
      sf::Text(Font,
               "and make wind correction by reversing wind power multiplying "
               "it on distance and adding to aim",
               40);
  sf::Text TutorialText3 = sf::Text(
      Font, "Get as many score as can in 120 seconds. H to hide tutorial", 40);
  sf::Texture Background, UI, Cell;
  sf::Sprite BGSprite, UISprite;
  std::vector<sf::Sprite> Cells = {};

  void Tick();
  Enemy* NewTarget();
};
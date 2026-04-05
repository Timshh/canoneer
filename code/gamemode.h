#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "score.h"
#include "canon.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  Score* Scores;
  Canon* Weapon;
  sf::RenderWindow* Window;
  int WindX, WindY, Distance, EnemyCoord;

  sf::SoundBuffer *HitBuffer;
  sf::Sound* HitSound;
  sf::Clock Time;
  sf::Font Font;
  sf::Text WindXText = sf::Text(Font, "", 50);
  sf::Text WindYText = sf::Text(Font, "", 50);
  sf::Text EnemyXText = sf::Text(Font, "", 50);
  sf::Text EnemyYText = sf::Text(Font, "", 50);
  sf::Text DistanceText = sf::Text(Font, "", 50);
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
  sf::Text TutorialText3 =
      sf::Text(Font, "Get as many score as can in 120 seconds", 40);
  sf::Texture Background, UI, Cell;
  sf::Sprite *BGSprite, *UISprite;
  std::vector<sf::Sprite> Cells = {};

  void Tick();
  void NewTarget(int* Distance, int* WindX, int* WindY, int* EnemyCoord);
};
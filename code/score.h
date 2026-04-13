#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetManager.h"

class Score {
 public:
  Score(sf::RenderWindow* window, AssetManager* manager);

  sf::RenderWindow* Window;
  int Scores = 0;
  float TimeLeft = 120;
  bool GameOver = false;
  sf::Sound EndSound;
  sf::Font* Font;
  sf::Text TimeText, ScoreText;

  void AddScore(int scores);
  void Tick(float deltatime);
};
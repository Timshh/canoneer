#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "assetManager.h"

class Score {
 public:
  Score(sf::RenderWindow* const window, AssetManager* const manager);

  sf::RenderWindow* Window;

  bool GameOver = false;
  void AddScore(const int scores);
  void Tick(const float deltatime);

 private:
  int Scores = 0, HiScore = 0;
  float TimeLeft = 120;
  sf::Sound EndSound;
  sf::Text TimeText, ScoreText, HiScoreText;
};
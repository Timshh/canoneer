#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "assetManager.h"

class Score {
 public:
  Score(sf::RenderWindow* const window, AssetManager* const manager);

  sf::RenderWindow* Window;
  AssetManager* Manager;

  bool GameOver = true;
  void AddScore(const int scores);
  void Tick(const float deltatime);
  void Reset();

 private:
  int Scores = 0, HiScore = 0;
  float TimeLeft = 0;
  sf::Sound StartSound, EndSound;
  sf::Text TimeText, ScoreText, HiScoreText;
};
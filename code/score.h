#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "assetManager.h"

class Score {
 public:
  Score(sf::RenderWindow* window, AssetManager* manager);

  sf::RenderWindow* Window;
  std::fstream* File;

  int Scores = 0, HiScore = 0;
  float TimeLeft = 120;
  bool GameOver = false;
  sf::Sound EndSound;
  sf::Text TimeText, ScoreText, HiScoreText;

  void AddScore(int scores);
  void Tick(float deltatime);
};
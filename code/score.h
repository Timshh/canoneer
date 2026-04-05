#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Score {
 public:
  Score(sf::RenderWindow* window, std::string font);

  sf::RenderWindow* Window;
  int Scores = 0;
  float TimeLeft = 120;
  bool GameOver = 0;
  sf::SoundBuffer *EndBuffer;
  sf::Sound *EndSound;
  sf::Font Font;
  sf::Text TimeText = sf::Text(Font, "", 50);
  sf::Text ScoreText = sf::Text(Font, "", 50);

  void AddScore(int scores);
  void Tick(float deltatime);
};
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Score {
 public:
  Score(sf::RenderWindow* window, sf::Font* font);

  sf::RenderWindow* Window;
  int Scores = 0;
  float TimeLeft = 120;
  bool GameOver = false;
  sf::SoundBuffer* EndBuffer;
  sf::Sound* EndSound;
  sf::Font* Font;
  sf::Text TimeText, ScoreText;

  void AddScore(int scores);
  void Tick(float deltatime);
};
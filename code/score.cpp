#include "score.h"

Score::Score(sf::RenderWindow* window, std::string font) {
  Window = window;
  Font.openFromFile(font);
  TimeText.setFillColor(sf::Color::Black);
  ScoreText.setFillColor(sf::Color::Black);
  TimeText.setPosition(sf::Vector2(106.0f, 322.0f));
  ScoreText.setPosition(sf::Vector2(106.0f, 414.0f));
}

void Score::AddScore(int scores) { Scores += scores; }

void Score::Tick(float deltatime) {
  TimeLeft -= deltatime;
  if (TimeLeft <= 0) {
    GameOver = 1;
    EndBuffer = new sf::SoundBuffer();
    EndBuffer->loadFromFile("data/Ending.wav");
    EndSound = new sf::Sound(*EndBuffer);
    EndSound->play();
  }
  ScoreText.setString(std::to_string(Scores));
  Window->draw(ScoreText);
  TimeText.setString(std::to_string((int)TimeLeft));
  Window->draw(TimeText);
}
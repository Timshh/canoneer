#include "score.h"

Score::Score(sf::RenderWindow* window, AssetManager* manager)
    : TimeText(manager->Font, "", 50),
      ScoreText(manager->Font, "", 50),
      EndSound(manager->End) {
  Window = window;
  TimeText.setFillColor(sf::Color::Black);
  ScoreText.setFillColor(sf::Color::Black);
  TimeText.setPosition(sf::Vector2f(106.0, 322.0));
  ScoreText.setPosition(sf::Vector2f(106.0, 414.0));
}

void Score::AddScore(int scores) { Scores += scores; }

void Score::Tick(float deltatime) {
  TimeLeft -= deltatime;
  if (TimeLeft <= 0) {
    GameOver = true;
    EndSound.play();
  }
  ScoreText.setString(std::to_string(Scores));
  Window->draw(ScoreText);
  TimeText.setString(std::to_string(static_cast<int>(TimeLeft)));
  Window->draw(TimeText);
}
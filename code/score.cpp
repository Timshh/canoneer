#include "score.h"

Score::Score(sf::RenderWindow* const window, AssetManager* const manager)
    : TimeText(manager->Font, "", 50),
      ScoreText(manager->Font, "", 50),
      HiScoreText(manager->Font, "", 50),
      EndSound(manager->End) {
  std::fstream File("data/hiscore.txt", std::ios::in);
  if (File >> HiScore) {
  }
  File.close();
  HiScoreText.setString(std::to_string(HiScore));

  Window = window;
  TimeText.setFillColor(sf::Color::Black);
  ScoreText.setFillColor(sf::Color::Black);
  HiScoreText.setFillColor(sf::Color::Black);
  TimeText.setPosition(sf::Vector2f(106.0, 414.0));
  ScoreText.setPosition(sf::Vector2f(106.0, 322.0));
  HiScoreText.setPosition(sf::Vector2f(106.0, 230.0));
}

void Score::AddScore(const int scores) { Scores += scores; }

void Score::Tick(const float deltatime) {
  // Timer
  if (!GameOver) {
    TimeLeft -= deltatime;
    if (TimeLeft <= 0) {
      GameOver = true;
      EndSound.play();
      std::ofstream File("data/hiscore.txt", std::ios::trunc);
      File << std::max(HiScore, Scores);
      File.close();
    }
  }
  // Draw
  ScoreText.setString(std::to_string(Scores));
  TimeText.setString(std::to_string(static_cast<int>(TimeLeft)));
  Window->draw(ScoreText);
  Window->draw(HiScoreText);
  Window->draw(TimeText);
}
#include "score.h"

Score::Score(sf::RenderWindow* const window, AssetManager* const manager)
    : TimeText(manager->Font, "", manager->TextSizeMid),
      ScoreText(manager->Font, "", manager->TextSizeMid),
      HiScoreText(manager->Font, "", manager->TextSizeMid),
      StartSound(manager->Start) , EndSound(manager->End) {
  std::fstream File(manager->HiScorePath, std::ios::in);
  if (File >> HiScore) {
  }
  File.close();
  HiScoreText.setString(std::to_string(HiScore));

  Window = window;
  Manager = manager;
  TimeText.setFillColor(manager->MainColor);
  ScoreText.setFillColor(manager->MainColor);
  HiScoreText.setFillColor(manager->MainColor);
  TimeText.setPosition(sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow3));
  ScoreText.setPosition(sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow2));
  HiScoreText.setPosition(
      sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow1));
}

void Score::AddScore(const int scores) {
  Scores += scores;
  if (GameOver) {
    std::ofstream File("data/hiscore.txt", std::ios::trunc);
    HiScore = std::max(HiScore, Scores);
    File << HiScore;
    File.close();
  }
}

void Score::Tick(const float deltatime) {
  // Timer
  if (!GameOver) {
    TimeLeft -= deltatime;
    if (TimeLeft <= 0) {
      GameOver = true;
      EndSound.play();
      std::ofstream File("data/hiscore.txt", std::ios::trunc);
      HiScore = std::max(HiScore, Scores);
      File << HiScore;
      File.close();
    }
  }
  if (GameOver) {
    HiScoreText.setString(std::to_string(HiScore));
  }
  // Draw
  ScoreText.setString(std::to_string(Scores));
  TimeText.setString(std::to_string(static_cast<int>(TimeLeft)));
  Window->draw(ScoreText);
  Window->draw(HiScoreText);
  Window->draw(TimeText);
}

void Score::Reset() {
  TimeLeft = Manager->GameTime;
  Scores = 0;
  StartSound.play();
}
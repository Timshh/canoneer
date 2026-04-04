#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

void NewTarget(int* Distance, int* WindX, int* WindY, int* EnemyCoord) {
  *Distance = rand() % 3 + 1;
  *WindX = rand() % 3 - 1;
  if (*Distance > 2) {
    *WindY = 0;
  } else {
    *WindY = rand() % 3 - 1;
  }
  int enemyX = rand() % 3 + 3;
  int enemyY = (rand() % 3 + 2) * 9;
  *EnemyCoord = enemyX + enemyY;
}

int main() {
  srand(time(NULL));
  int AimCoord = 0, Charges = 0, ShotCharges, Score = 0, ShotCoord, WindX,
      WindY, Distance, EnemyCoord;
  float TimeLeft = 120, CD = 0, FlyTime = 0;
  bool RightPressed = 0, LeftPressed = 0, UpPressed = 0, DownPressed = 0,
       CanFire = 1, Shot = 0, LmbPressed = 0, RmbPressed = 0, GameOver = 0;
  sf::Clock Time;
  sf::RenderWindow Window(sf::VideoMode({1920, 1080}), "Canoneer",
                          sf::State::Fullscreen);
  sf::Font Font;
  Font.openFromFile("graphics/Roboto.ttf");
  sf::Text TimeText(Font, "", 40);
  TimeText.setFillColor(sf::Color(0, 0, 0, 255));
  TimeText.setPosition(sf::Vector2(106.0f, 330.0f));
  sf::Text ScoreText(Font, "", 40);
  ScoreText.setFillColor(sf::Color(0, 0, 0, 255));
  ScoreText.setPosition(sf::Vector2(106.0f, 422.0f));
  sf::Text TimerText(Font, "", 40);
  TimerText.setFillColor(sf::Color(0, 0, 0, 255));
  TimerText.setPosition(sf::Vector2(106.0f, 606.0f));
  sf::Text ChargesText(Font, "", 40);
  ChargesText.setFillColor(sf::Color(0, 0, 0, 255));
  ChargesText.setPosition(sf::Vector2(106.0f, 698.0f));
  sf::Text WindXText(Font, "", 40);
  WindXText.setFillColor(sf::Color(0, 0, 0, 255));
  WindXText.setPosition(sf::Vector2(1734.0f, 330.0f));
  sf::Text WindYText(Font, "", 40);
  WindYText.setFillColor(sf::Color(0, 0, 0, 255));
  WindYText.setPosition(sf::Vector2(1734.0f, 422.0f));
  sf::Text EnemyXText(Font, "", 40);
  EnemyXText.setFillColor(sf::Color(0, 0, 0, 255));
  EnemyXText.setPosition(sf::Vector2(1734.0f, 514.0f));
  sf::Text EnemyYText(Font, "", 40);
  EnemyYText.setFillColor(sf::Color(0, 0, 0, 255));
  EnemyYText.setPosition(sf::Vector2(1734.0f, 606.0f));
  sf::Text DistanceText(Font, "", 40);
  DistanceText.setFillColor(sf::Color(0, 0, 0, 255));
  DistanceText.setPosition(sf::Vector2(1734.0f, 698.0f));

  sf::Texture Background;
  Background.loadFromFile("graphics/BG.png");
  sf::Sprite BGSprite(Background);

  sf::Texture UI;
  UI.loadFromFile("graphics/ArtUI.png");
  sf::Sprite UISprite(UI);
  UISprite.setPosition(sf::Vector2(0.0f, 0.0f));

  sf::Texture Cell;
  Cell.loadFromFile("graphics/Cell.png");

  sf::Texture Aim;
  Aim.loadFromFile("graphics/Aim.png");
  sf::Sprite AimSprite(Aim);

  sf::Texture Canon;
  Canon.loadFromFile("graphics/Canon.png");
  sf::Sprite CanonSprite(Canon);

  sf::Texture Ready;
  Ready.loadFromFile("graphics/Ready.png");

  sf::Texture NonReady;
  NonReady.loadFromFile("graphics/NonReady.png");

  std::vector<sf::Sprite> Cells;
  for (int i = 0; i < 63; i++) {
    sf::Sprite NewCell(Cell);
    float x = i % 9;
    float y = trunc(i / 9);
    NewCell.setPosition(
        sf::Vector2(sf::Vector2(546.0f + 92.0f * x, 218.0f + 92.0f * y)));
    Cells.push_back(NewCell);
  }

  NewTarget(&Distance, &WindX, &WindY, &EnemyCoord);

  while (Window.isOpen()) {
    // Timers
    float deltatime = Time.restart().asSeconds();
    if (!GameOver) {
      TimeLeft -= deltatime;
      if (TimeLeft <= 0) {
        GameOver = 1;
      }
      if (!CanFire) {
        CD -= deltatime;
        if (CD <= 0) {
          CanFire = 1;
        }
      }
      if (Shot) {
        FlyTime -= deltatime;
        if (FlyTime <= 0) {
          Shot = false;
          if (ShotCoord ==
                  EnemyCoord - WindX * Distance - WindY * 9 * Distance and
              Distance == ShotCharges) {
            Score++;
            NewTarget(&Distance, &WindX, &WindY, &EnemyCoord);
          }
        }
      }
    }

    // Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      Window.close();
    }
    if (!GameOver) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        if (AimCoord >= 1 and !RightPressed and AimCoord % 9 != 0) {
          RightPressed = 1;
          AimCoord -= 1;
        }
      } else {
        RightPressed = 0;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        if (AimCoord <= 61 and !LeftPressed and AimCoord % 9 != 8) {
          LeftPressed = 1;
          AimCoord += 1;
        }
      } else {
        LeftPressed = 0;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (AimCoord >= 9 and !UpPressed) {
          AimCoord -= 9;
          UpPressed = 1;
        }
      } else {
        UpPressed = 0;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (AimCoord <= 53 and !DownPressed) {
          AimCoord += 9;
          DownPressed = 1;
        }
      } else {
        DownPressed = 0;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (CanFire and Charges != 0 and !LmbPressed) {
          CanFire = 0;
          CD = 5;
          FlyTime = 3 * Charges;
          ShotCoord = AimCoord;
          ShotCharges = Charges;
          Charges = 0;
          Shot = 1;
          LmbPressed = 1;
        }
      } else {
        LmbPressed = 0;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        if (Charges < 3 and !RmbPressed) {
          Charges += 1;
          RmbPressed = 1;
        }
      } else {
        RmbPressed = 0;
      }
    }

    // Sprites position
    BGSprite.setPosition(sf::Vector2(0.0f, 0.0f));
    float AimX = AimCoord % 9;
    float AimY = trunc(AimCoord / 9);
    AimSprite.setPosition(
        sf::Vector2(546.0f + 92.0f * AimX, 218.0f + 92.0f * AimY));
    CanonSprite.setPosition(sf::Vector2(546.0f + 92.0f * (AimX * 0.2f + 2.1f),
                                        218.0f + 92.0f * (AimY * 0.2f)));

    // Draw
    Window.clear();
    Window.draw(BGSprite);
    Window.draw(CanonSprite);
    Window.draw(UISprite);
    Window.draw(AimSprite);
    for (int i = 0; i < 63; i++) {
      Window.draw(Cells[i]);
    }
    if (CanFire) {
      sf::Sprite ReadySprite(Ready);
      ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
      Window.draw(ReadySprite);
    } else {
      sf::Sprite ReadySprite(NonReady);
      ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
      Window.draw(ReadySprite);
    }

    ScoreText.setString(std::to_string(Score));
    Window.draw(ScoreText);

    TimerText.setString(std::to_string((int)FlyTime));
    Window.draw(TimerText);

    TimeText.setString(std::to_string((int)TimeLeft));
    Window.draw(TimeText);

    ChargesText.setString(std::to_string(Charges));
    Window.draw(ChargesText);

    DistanceText.setString(std::to_string(Distance));
    Window.draw(DistanceText);

    WindXText.setString(std::to_string((int)WindX));
    Window.draw(WindXText);

    WindYText.setString(std::to_string((int)WindY));
    Window.draw(WindYText);

    EnemyXText.setString(std::to_string(EnemyCoord % 9 + 1));
    Window.draw(EnemyXText);

    EnemyYText.setString(std::to_string((int)(EnemyCoord / 9) + 1));
    Window.draw(EnemyYText);

    Window.display();
  }
  return 0;
}
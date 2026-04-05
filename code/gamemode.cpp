#include <gamemode.h>

Gamemode::Gamemode(sf::RenderWindow* window) {
  Window = window;
  Font.openFromFile("data/Tiny5.ttf");
  Scores = new Score(Window, "data/Tiny5.ttf");
  Weapon = new Canon(Window, "data/Tiny5.ttf");
  WindYText.setFillColor(sf::Color::Black);
  DistanceText.setFillColor(sf::Color::Black);
  WindXText.setFillColor(sf::Color::Black);
  EnemyXText.setFillColor(sf::Color::Black);
  EnemyYText.setFillColor(sf::Color::Black);
  TutorialText.setFillColor(sf::Color::Black);
  TutorialText2.setFillColor(sf::Color::Black);
  TutorialText3.setFillColor(sf::Color::Black);
  
  WindXText.setPosition(sf::Vector2(1734.0f, 322.0f));
  WindYText.setPosition(sf::Vector2(1734.0f, 414.0f));
  EnemyXText.setPosition(sf::Vector2(1734.0f, 506.0f));
  EnemyYText.setPosition(sf::Vector2(1734.0f, 598.0f));
  DistanceText.setPosition(sf::Vector2(1734.0f, 690.0f));
  
  TutorialText.setPosition(sf::Vector2(50.0f, 900.0f));
  TutorialText2.setPosition(sf::Vector2(50.0f, 950.0f));
  TutorialText3.setPosition(sf::Vector2(50.0f, 1000.0f));

  Background.loadFromFile("data/BG.png");
  UI.loadFromFile("data/ArtUI.png");
  Cell.loadFromFile("data/Cell.png");
  
  BGSprite = new sf::Sprite(Background);
  UISprite = new sf::Sprite(UI);
  UISprite->setPosition(sf::Vector2(0.0f, 0.0f));

  for (int i = 0; i < 63; i++) {
    sf::Sprite NewCell(Cell);
    float x = i % 9;
    float y = trunc(i / 9);
    NewCell.setPosition(
        sf::Vector2(sf::Vector2(546.0f + 92.0f * x, 218.0f + 92.0f * y)));
    Cells.push_back(NewCell);
  }

  NewTarget(&Distance, &WindX, &WindY, &EnemyCoord);
}

void Gamemode::NewTarget(int* Distance, int* WindX, int* WindY, int* EnemyCoord) {
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

void Gamemode::Tick() {
  // Timers
  float deltatime = Time.restart().asSeconds();
  if (!Scores->GameOver) {
    // Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      Window->close();
    }

    // Sprites position
    BGSprite->setPosition(sf::Vector2(0.0f, 0.0f));

    // Draw
    Window->clear();
    Window->draw(*BGSprite);

    Weapon->DrawCanon();

    Window->draw(*UISprite);

    if (Weapon->Tick(deltatime)) {
      if (Weapon->ShotCoord ==
              EnemyCoord - WindX * Distance - WindY * 9 * Distance and
          Distance == Weapon->ShotCharges) {
        Scores->AddScore(1);
        NewTarget(&Distance, &WindX, &WindY, &EnemyCoord);
        HitBuffer = new sf::SoundBuffer();
        HitBuffer->loadFromFile("data/Hit.wav");
        HitSound = new sf::Sound(*HitBuffer);
        HitSound->play();
      } else {
        HitBuffer = new sf::SoundBuffer();
        HitBuffer->loadFromFile("data/Miss.wav");
        HitSound = new sf::Sound(*HitBuffer);
        HitSound->play();
      }
    }

    for (int i = 0; i < 63; i++) {
      Window->draw(Cells[i]);
    }

    Scores->Tick(deltatime);

    DistanceText.setString(std::to_string(Distance));
    Window->draw(DistanceText);

    WindXText.setString(std::to_string((int)WindX));
    Window->draw(WindXText);

    WindYText.setString(std::to_string((int)WindY));
    Window->draw(WindYText);

    EnemyXText.setString(std::to_string(EnemyCoord % 9 + 1));
    Window->draw(EnemyXText);

    EnemyYText.setString(std::to_string((int)(EnemyCoord / 9) + 1));
    Window->draw(EnemyYText);

    Window->draw(TutorialText);
    Window->draw(TutorialText2);
    Window->draw(TutorialText3);

    Window->display();
  }
}
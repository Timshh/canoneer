#include <gamemode.h>

Gamemode::Gamemode(sf::RenderWindow* window)
    : Background(sf::Texture("data/BG.png")),
      UI(sf::Texture("data/ArtUI.png")),
      Cell(sf::Texture("data/Cell.png")),
      BGSprite(Background), UISprite(UI) {
  Window = window;
  Font.openFromFile(FontPath);
  Scores = new Score(Window, &Font);
  Weapon = new Canon(Window, &Font);
  TutorialText.setFillColor(sf::Color::Black);
  TutorialText2.setFillColor(sf::Color::Black);
  TutorialText3.setFillColor(sf::Color::Black);
  TutorialText.setPosition(sf::Vector2(50.0f, 900.0f));
  TutorialText2.setPosition(sf::Vector2(50.0f, 950.0f));
  TutorialText3.setPosition(sf::Vector2(50.0f, 1000.0f));

  

  UISprite.setPosition(sf::Vector2(0.0f, 0.0f));

  for (int i = 0; i < 63; i++) {
    sf::Sprite NewCell(Cell);
    float x = i % 9;
    float y = trunc(i / 9);
    NewCell.setPosition(
        sf::Vector2(sf::Vector2(546.0f + 92.0f * x, 218.0f + 92.0f * y)));
    Cells.push_back(NewCell);
  }

  Target = NewTarget();
}

Enemy* Gamemode::NewTarget() {
  int distance = rand() % 3 + 1;
  int windX = rand() % 3 - 1;
  int windY;
  if (distance > 2) {
    windY = 0;
  } else {
    windY = rand() % 3 - 1;
  }
  int enemyX = rand() % 3 + 3;
  int enemyY = (rand() % 3 + 2) * 9;
  int enemyCoord = enemyX + enemyY;
  return new Enemy(Window, &Font, enemyCoord, windX, windY, distance);
}

void Gamemode::Tick() {
  // Timers
  float deltatime = Time.restart().asSeconds();
  if (!Scores->GameOver) {
    // Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      Window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
      if (!HPressed) {
        TutorialHidden = !TutorialHidden;
        HPressed = true;
      }
    } else {
      HPressed = false;
    }

    // Sprites position
    BGSprite.setPosition(sf::Vector2(0.0f, 0.0f));

    // Draw
    Window->clear();
    Window->draw(BGSprite);

    Weapon->DrawCanon();

    Window->draw(UISprite);

    if (Target->Tick(deltatime)) {
      delete Target;
      Scores->AddScore(1);
      Target = NewTarget();
    }

    Weapon->Tick(deltatime, Target);

    for (int i = 0; i < 63; i++) {
      Window->draw(Cells[i]);
    }

    Scores->Tick(deltatime);

    if (!TutorialHidden) {
      Window->draw(TutorialText);
      Window->draw(TutorialText2);
      Window->draw(TutorialText3);
    }

    Window->display();
  }
}
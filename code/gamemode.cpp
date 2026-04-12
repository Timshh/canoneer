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
  TutorialText.setPosition(sf::Vector2f(50.0, 900.0));
  TutorialText2.setPosition(sf::Vector2f(50.0, 950.0));
  TutorialText3.setPosition(sf::Vector2f(50.0, 1000.0));

  

  UISprite.setPosition(sf::Vector2f(0.0, 0.0));

  for (int i = 0; i < 63; i++) {
    sf::Sprite NewCell(Cell);
    float x = i % 9;
    float y = trunc(i / 9);
    NewCell.setPosition(
        sf::Vector2f(sf::Vector2f(546.0 + 92.0 * x, 218.0 + 92.0 * y)));
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
  }
  if (!Scores->GameOver) {
    // Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
      if (!HPressed) {
        TutorialHidden = !TutorialHidden;
        HPressed = true;
      }
    } else {
      HPressed = false;
    }

    // Sprites position
    BGSprite.setPosition(sf::Vector2f(0.0, 0.0));

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
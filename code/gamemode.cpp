#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* const window, AssetManager* const manager)
    : BarrierSprite(manager->Barrier),
      UISprite(manager->UI),
      TutorialText(manager->Font,
                   manager->Tutorial1Text,
                   manager->TextSizeSmall),
      TutorialText2(
          manager->Font, manager->Tutorial2Text,
          manager->TextSizeSmall),
      TutorialText3(
          manager->Font, manager->Tutorial3Text,
          manager->TextSizeSmall),
      HintText(manager->Font, manager->HintText,
               manager->TextSizeBig),
      BG(Background(window, manager)) {
  Manager = manager;
  Window = window;
  Scores = std::make_unique<Score>(Window, Manager);
  Weapon = std::make_unique<Canon>(Window, Manager);
  TutorialText.setFillColor(Manager->MainColor);
  TutorialText2.setFillColor(Manager->MainColor);
  TutorialText3.setFillColor(Manager->MainColor);
  HintText.setFillColor(Manager->MainColor);
  TutorialText.setPosition(Manager->Tutorial1Position);
  TutorialText2.setPosition(Manager->Tutorial2Position);
  TutorialText3.setPosition(Manager->Tutorial3Position);
  HintText.setPosition(Manager->HintPosition);

  BarrierSprite.setPosition(sf::Vector2f(0, BarrierPosition));
  UISprite.setPosition(sf::Vector2f(0, 0));

  for (int i = 0; i < Manager->GridSize; i++) {
    sf::Sprite NewCell(Manager->Cell);
    float x = i % Manager->Columns;
    float y = trunc(i / Manager->Columns);
    NewCell.setPosition(sf::Vector2f(
        sf::Vector2f(Manager->GridStartX + Manager->CellSize * x,
                     Manager->GridStartY + Manager->CellSize * y)));
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
  int enemyY = (rand() % 3 + 2) * Manager->Columns;
  int enemyCoord = enemyX + enemyY;
  return new Enemy(Window, Manager, enemyCoord, windX, windY, distance,
                   rand() % 3);
}

void Gamemode::Tick() {
  // Timers
  float deltatime = Time.restart().asSeconds();
  // Input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
  }
  if (!Scores->GameOver) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
      if (!HPressed) {
        TutorialHidden = !TutorialHidden;
        HPressed = true;
      }
    } else {
      HPressed = false;
    }
    Weapon->TickInput();
  }
  BG.SetOffset(Weapon->GetOffset(deltatime));

  // Draw
  Window->clear();
  BG.Tick(deltatime);
  Weapon->Tick(deltatime, Target);
  for (int i = 0; i < Manager->GridSize; i++) {
    Window->draw(Cells[i]);
  }
  if (Scores->GameOver) {
    if (BarrierPosition != 0) {
      BarrierPosition = std::min(0.0f, BarrierPosition + deltatime * BarrierDelta);
    }
    BarrierSprite.setPosition(
        sf::Vector2f(0, floor(BarrierPosition / BarrierDelta) * BarrierDelta));
  }
  Window->draw(BarrierSprite);
  Window->draw(UISprite);

  if (Target->Tick(deltatime)) {
    delete Target;
    Scores->AddScore(1);
    Target = NewTarget();
  }

  Weapon->SubRender();
  Scores->Tick(deltatime);

  if (!TutorialHidden) {
    Window->draw(TutorialText);
    Window->draw(TutorialText2);
    Window->draw(TutorialText3);
  }
  Window->draw(HintText);

  Window->display();
}
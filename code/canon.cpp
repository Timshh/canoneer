#include "canon.h"

Canon::Canon(sf::RenderWindow* const window, AssetManager* const manager)
    : CanonSprite(manager->Canon),
      AimSprite(manager->Aim),
      ReadySprite(manager->Ready),
      HitSprite(manager->NonReady),
      TimerText(manager->Font, "", manager->TextSizeMid),
      ChargesText(manager->Font, "", manager->TextSizeMid),
      TypeText(manager->Font, "", manager->TextSizeMid),
      ShotSound(manager->ShotWeak) {
  Window = window;
  Manager = manager;
  TimerText.setFillColor(manager->MainColor);
  ChargesText.setFillColor(manager->MainColor);
  TypeText.setFillColor(manager->MainColor);
  TimerText.setPosition(sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow5));
  ChargesText.setPosition(
      sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow6));
  TypeText.setPosition(sf::Vector2f(manager->LeftHUDColumn, manager->HUDRow7));
  ReadySprite.setPosition(
      sf::Vector2f(manager->LeftHUDColumn - manager->LampOffsetX,
                   manager->HUDRow4 - manager->LampOffsetY));
  HitSprite.setPosition(sf::Vector2f(manager->RightHUDColumn,
                                     manager->HUDRow7 - manager->LampOffsetY));
  TimerText.setString("0");
}

void Canon::Tick(const float deltatime, Enemy* const target) {
  Target = target;
  if (Explode) {
    if (Explode->Tick(deltatime, ShakeFloor)) {
      Explode.reset();
    }
  }

  if (Shot) {
    if (!Shot->Tick(deltatime, ShakeFloor)) {
      TimerText.setString(std::to_string((int)Shot->FlyTime));
    } else {
      if (!Target->Alive) {
        HitSprite.setTexture(Manager->Ready);
        HitTime = 1;
      }
      Explode = std::make_unique<Explosion>(
          Window, Manager,
          Shot->ShotCoord + Target->WindX * Shot->ShotCharges +
              Target->WindY * Manager->Columns * Shot->ShotCharges,
          Shot->ShotCharges, !Target->Alive);
      Shot.reset();
      TimerText.setString("0");
      ReadySprite.setTexture(Manager->Ready);
    }
  }

  if (FireTime > 0) {
    FireTime -= deltatime;
    if (FireTime <= 0) {
      CanonSprite.setTexture(Manager->Canon);
    }
  }
  if (HitTime > 0) {
    HitTime -= deltatime;
    if (HitTime <= 0) {
      HitSprite.setTexture(Manager->NonReady);
    }
  }

  float AimX = AimCoord % Manager->Columns;
  float AimY = static_cast<int>(AimCoord / Manager->Columns);
  AimSprite.setPosition(
      sf::Vector2f(Manager->GridStartX + Manager->CellSize * AimX,
                   Manager->GridStartY + Manager->CellSize * AimY));
  CanonSprite.setPosition(
      sf::Vector2f(Manager->GridStartX + Manager->CellSize * (AimX * 0.2 + 2.1),
                   Manager->GridStartY + Manager->CellSize * (AimY * 0.2)));

  Window->draw(CanonSprite);
  Window->draw(AimSprite);
}

void Canon::TickInput() {
  if (!Shot) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      if (AimCoord >= 1 && !LeftPressed &&
          AimCoord % Manager->Columns != 0) {
        AimCoord -= 1;
        LeftPressed = true;
      }
    } else {
      LeftPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      if (AimCoord <= Manager->GridSize - 2 && !RightPressed &&
          AimCoord % Manager->Columns != (Manager->Columns - 1)) {
        AimCoord += 1;
        RightPressed = true;
      }
    } else {
      RightPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      if (AimCoord >= Manager->Columns && !UpPressed) {
        AimCoord -= Manager->Columns;
        UpPressed = true;
      }
    } else {
      UpPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      if (AimCoord <= Manager->GridSize - 1 - Manager->Columns && !DownPressed) {
        AimCoord += 9;
        DownPressed = true;
      }
    } else {
      DownPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
      if (!Shot && Charges != 0 && !ZPressed) {
        switch (Charges) {
          case 1:
            ShotSound.setBuffer(Manager->ShotWeak);
            break;
          case 2:
            ShotSound.setBuffer(Manager->ShotMid);
            break;
          case 3:
            ShotSound.setBuffer(Manager->ShotHeavy);
            break;
        }
        CanonSprite.setTexture(Manager->CanonFire);
        FireTime = FireTimeMult + Charges * FireTimeMult;
        Shake = ShakeMult * 2 + Charges * ShakeMult;
        ShotSound.play();
        Shot = std::make_unique<Bullet>(Window, Target, Manager, AimCoord,
                                        Charges, Type);
        Charges = Type = 0;
        ReadySprite.setTexture(Manager->NonReady);
        ZPressed = true;
      }
    } else {
      ZPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
      if (Charges < 3 && !XPressed) {
        Charges += 1;
        XPressed = true;
      }
    } else {
      XPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
      if (!CPressed) {
        Type = (Type + 1) % 3;
        CPressed = true;
      }
    } else {
      CPressed = false;
    }
  }
}

void Canon::Reset() {
  Charges = 0;
  AimCoord = 0;
  Type = 0;
}

float Canon::GetOffset(const float deltatime) {
  if (Shake != 0) {
    Shake = std::max(0.0f, Shake - deltatime * ShakeMult);
    ShakeFloor = floor(Shake / ShakeMult) * ShakeMult;
  }
  return ShakeFloor;
}

void Canon::SubRender() {
  ChargesText.setString(std::to_string(Charges));
  switch (Type) {
    case 0:
      TypeText.setString("Frag");
      break;
    case 1:
      TypeText.setString("HE");
      break;
    case 2:
      TypeText.setString("Flak");
      break;
  }

  Window->draw(ReadySprite);
  Window->draw(HitSprite);
  Window->draw(ChargesText);
  Window->draw(TypeText);
  Window->draw(TimerText);
}
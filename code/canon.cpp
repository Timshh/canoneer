#include "canon.h"

Canon::Canon(sf::RenderWindow* window, AssetManager* manager)
    : CanonSprite(manager->Canon),
      AimSprite(manager->Aim),
      ReadySprite(manager->Ready),
      HitSprite(manager->NonReady),
      TimerText(manager->Font, "", 50),
      ChargesText(manager->Font, "", 50),
      TypeText(manager->Font, "", 50),
      ShotSound(manager->ShotWeak) {
  Window = window;
  Manager = manager;
  TimerText.setFillColor(sf::Color::Black);
  ChargesText.setFillColor(sf::Color::Black);
  TypeText.setFillColor(sf::Color::Black);
  TimerText.setPosition(sf::Vector2f(106.0, 598.0));
  ChargesText.setPosition(sf::Vector2f(106.0, 690.0));
  TypeText.setPosition(sf::Vector2f(100.0, 776.0));
  ReadySprite.setPosition(sf::Vector2f(96.0, 494.0));
  HitSprite.setPosition(sf::Vector2f(1560.0, 762.0));
  TimerText.setString("0");
}

void Canon::Tick(float deltatime, Enemy* target) {
  Target = target;
  if (Explode) {
    if (Explode->Tick(deltatime)) {
      delete Explode;
      Explode = nullptr;
      
    }
  }
  // Input
  if (!Shot) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      if (AimCoord >= 1 and !RightPressed and AimCoord % 9 != 0) {
        AimCoord -= 1;
        RightPressed = true;
      }
    } else {
      RightPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      if (AimCoord <= 61 and !LeftPressed and AimCoord % 9 != 8) {
        AimCoord += 1;
        LeftPressed = true;
      }
    } else {
      LeftPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      if (AimCoord >= 9 and !UpPressed) {
        AimCoord -= 9;
        UpPressed = true;
      }
    } else {
      UpPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      if (AimCoord <= 53 and !DownPressed) {
        AimCoord += 9;
        DownPressed = true;
      }
    } else {
      DownPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
      if (!Shot and Charges != 0 and !ZPressed) {
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
        FireTime = 0.2 + Charges * 0.2;
        ShotSound.play();
        Shot =
            new Bullet(Window, Target, Manager, AimCoord, Charges, 3 * Charges, Type);
        Charges = Type = 0;
        ReadySprite.setTexture(Manager->NonReady);
        ZPressed = true;
      }
    } else {
      ZPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
      if (Charges < 3 and !XPressed) {
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

  if (Shot) {
    if (!Shot->Tick(deltatime)) {
      TimerText.setString(std::to_string((int)Shot->FlyTime));
    } else {
      if (!Target->Alive) {
        HitSprite.setTexture(Manager->Ready);
        HitTime = 1;
      }
      Explode =
          new Explosion(Window, Manager,
                        Shot->ShotCoord + Target->WindX * Shot->ShotCharges +
                            Target->WindY * 9 * Shot->ShotCharges,
                        Shot->ShotCharges, !Target->Alive);
      delete Shot;
      Shot = nullptr;
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

  float AimX = AimCoord % 9;
  float AimY = static_cast<int>(AimCoord / 9);
  AimSprite.setPosition(sf::Vector2f(546 + 92 * AimX, 218 + 92 * AimY));
  CanonSprite.setPosition(
      sf::Vector2f(546 + 92 * (AimX * 0.2 + 2.1), 218 + 92 * (AimY * 0.2)));

  Window->draw(CanonSprite);
  Window->draw(AimSprite);
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
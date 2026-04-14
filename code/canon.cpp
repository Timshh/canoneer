#include "canon.h"

Canon::Canon(sf::RenderWindow* window, AssetManager* manager)
    : CanonSprite(manager->Canon),
      AimSprite(manager->Aim),
      TimerText(manager->Font, "", 50),
      ChargesText(manager->Font, "", 50),
      ShotSound(manager->ShotWeak) {
  Window = window;
  Manager = manager;
  TimerText.setFillColor(sf::Color::Black);
  ChargesText.setFillColor(sf::Color::Black);
  TimerText.setPosition(sf::Vector2f(106.0, 598.0));
  ChargesText.setPosition(sf::Vector2f(106.0, 690.0));
}

void Canon::DrawCanon(float deltatime) {
  if (Explode) {
    if (Explode->Tick(deltatime)) {
      delete Explode;
      Explode = nullptr;
    }
  }
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!Shot and Charges != 0 and !LmbPressed) {
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
        ShotSound.play();
        Shot =
            new Bullet(Window, Target, Manager, AimCoord, Charges, 3 * Charges);
        Charges = 0;
        LmbPressed = true;
      }
    } else {
      LmbPressed = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
      if (Charges < 3 and !RmbPressed) {
        Charges += 1;
        RmbPressed = true;
      }
    } else {
      RmbPressed = false;
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

void Canon::Tick(float deltatime, Enemy* target) {
  Target = target;
  if (!Shot) {
    sf::Sprite ReadySprite(Manager->Ready);
    ReadySprite.setPosition(sf::Vector2f(100.0, 494.0));
    Window->draw(ReadySprite);
  } else {
    sf::Sprite ReadySprite(Manager->NonReady);
    ReadySprite.setPosition(sf::Vector2f(100.0, 494.0));
    Window->draw(ReadySprite);
  }

  ChargesText.setString(std::to_string(Charges));
  Window->draw(ChargesText);
  if (Shot) {
    if (!Shot->Tick(deltatime)) {
      TimerText.setString(std::to_string((int)Shot->FlyTime));
      Window->draw(TimerText);
      return;
    } else {
      Explode =
          new Explosion(Window, Manager,
                        Shot->ShotCoord + Target->WindX * Shot->ShotCharges +
                            Target->WindY * 9 * Shot->ShotCharges,
                        Shot->ShotCharges, !Target->Alive);
      delete Shot;
      Shot = 0;
    }
  }
  TimerText.setString("0");
  Window->draw(TimerText);
}
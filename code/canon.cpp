#include "canon.h"

Canon::Canon(sf::RenderWindow* window, sf::Font* font)
    : Aim(sf::Texture("data/Aim.png")),
      CanonTexture(sf::Texture("data/Canon.png")),
      Ready(sf::Texture("data/Ready.png")),
      NonReady(sf::Texture("data/NonReady.png")), 
      CanonSprite(CanonTexture),
      AimSprite(Aim),
      Font(font),
      TimerText(*Font, "", 50),
      ChargesText(*Font, "", 50) {
  Window = window;
  TimerText.setFillColor(sf::Color::Black);
  ChargesText.setFillColor(sf::Color::Black);
  TimerText.setPosition(sf::Vector2(106.0f, 598.0f));
  ChargesText.setPosition(sf::Vector2(106.0f, 690.0f));
}

void Canon::DrawCanon() {
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
        ShotBuffer = new sf::SoundBuffer();
        switch (Charges) {
          case 1:
            ShotBuffer->loadFromFile("data/FireWeak.wav");
            break;
          case 2:
            ShotBuffer->loadFromFile("data/FireMid.wav");
            break;
          case 3:
            ShotBuffer->loadFromFile("data/FireHeavy.wav");
            break;
        }
        if (ShotSound) {
          delete ShotSound;
        }
        ShotSound = new sf::Sound(*ShotBuffer);
        ShotSound->play();
        Shot = new Bullet(Window, Target, AimCoord, Charges, 3 * Charges);
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
  float AimY = (int)(AimCoord / 9);
  AimSprite.setPosition(
      sf::Vector2f(546 + 92 * AimX, 218 + 92 * AimY));
  CanonSprite.setPosition(sf::Vector2f(546 + 92 * (AimX * 0.2 + 2.1),
                                       218 + 92 * (AimY * 0.2)));
  Window->draw(CanonSprite);
  Window->draw(AimSprite);
}

void Canon::Tick(float deltatime, Enemy* target) {
  Target = target;
  if (!Shot) {
    sf::Sprite ReadySprite(Ready);
    ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
    Window->draw(ReadySprite);
  } else {
    sf::Sprite ReadySprite(NonReady);
    ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
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
      delete Shot;
      Shot = 0;
    }
  }
  TimerText.setString("0");
  Window->draw(TimerText);
}
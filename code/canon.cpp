#include "canon.h"

Canon::Canon(sf::RenderWindow* window, std::string font) {
  Window = window;
  Font.openFromFile(font);
  TimerText.setFillColor(sf::Color::Black);
  ChargesText.setFillColor(sf::Color::Black);
  TimerText.setPosition(sf::Vector2(106.0f, 598.0f));
  ChargesText.setPosition(sf::Vector2(106.0f, 690.0f));
  Aim.loadFromFile("data/Aim.png");
  CanonTexture.loadFromFile("data/Canon.png");
  Ready.loadFromFile("data/Ready.png");
  NonReady.loadFromFile("data/NonReady.png");
  CanonSprite = new sf::Sprite(CanonTexture);
  AimSprite = new sf::Sprite(Aim);
}

void Canon::DrawCanon() {
  if (!Shot) {
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
        ShotSound = new sf::Sound(*ShotBuffer);
        ShotSound->play();
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

  float AimX = AimCoord % 9;
  float AimY = trunc(AimCoord / 9);
  AimSprite->setPosition(
      sf::Vector2(546.0f + 92.0f * AimX, 218.0f + 92.0f * AimY));
  CanonSprite->setPosition(sf::Vector2(546.0f + 92.0f * (AimX * 0.2f + 2.1f),
                                       218.0f + 92.0f * (AimY * 0.2f)));
  Window->draw(*CanonSprite);
  Window->draw(*AimSprite);
}

bool Canon::Tick(float deltatime) {
  if (!Shot) {
    sf::Sprite ReadySprite(Ready);
    ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
    Window->draw(ReadySprite);
  } else {
    sf::Sprite ReadySprite(NonReady);
    ReadySprite.setPosition(sf::Vector2(100.0f, 494.0f));
    Window->draw(ReadySprite);
  }

  TimerText.setString(std::to_string((int)FlyTime));
  Window->draw(TimerText);

  ChargesText.setString(std::to_string(Charges));
  Window->draw(ChargesText);
  if (Shot) {
    FlyTime -= deltatime;
    if (FlyTime <= 0) {
      Shot = 0;
      return 1;
    }
  }
  return 0;
}
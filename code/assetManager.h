#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
 public:
  AssetManager(sf::RenderWindow* window);

  sf::SoundBuffer End, ShotWeak, ShotMid, ShotHeavy, Hit, Miss;
  sf::Texture Background, UI, Cell, Aim, Canon, Ready, NonReady, ExplosionFar,
      ExplosionMid, ExplosionNear;
  sf::Font Font;

};
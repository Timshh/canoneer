#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager {
 public:
  AssetManager();

  const std::string FontPath = "data/Tiny5.ttf";

  sf::SoundBuffer End, Shot1, Shot2, Shot3;
  sf::Font Font;

  sf::Font* GetFont();
};
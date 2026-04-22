#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
 public:
  AssetManager();

  sf::SoundBuffer Start, End, ShotWeak, ShotMid, ShotHeavy, Hit, Miss;
  sf::Texture Background, Barrier, UI, Cell, Aim, Canon, CanonFire, Ready,
      NonReady, ExplosionFar, ExplosionMid, ExplosionNear, Bullet;
  std::vector<sf::Texture> Clouds, Hedgehogs, Trees;
  sf::Font Font;

  const float CellSize = 92;
  const int Columns = 9;
  const int Rows = 7;
  const float TimeMult = 3;
  const int GridSize = Columns * Rows;
  const float GameTime = 120;
  const sf::Color MainColor = sf::Color::Black;
  const int TextSizeSmall = 40;
  const int TextSizeMid = 50;
  const int TextSizeBig = 60;

  const std::string HiScorePath = "data/hiscore.txt";


  const int LeftCloudBorder = 200;
  const int RightCloudBorder = 1420;
  const int DownCloudBorder = 0;
  const int UpCloudBorder = 450;

  const int LeftDecorBorder = 450;
  const int RightDecorBorder = 1450;
  const int DownDecorBorder = 550;
  const int UpDecorBorder = 900;

  const sf::Vector2f Tutorial1Position = sf::Vector2f(10, 900);
  const sf::Vector2f Tutorial2Position = sf::Vector2f(10, 950);
  const sf::Vector2f Tutorial3Position = sf::Vector2f(10, 1000);
  const sf::Vector2f HintPosition = sf::Vector2f(180.0, 30.0);
  const float LampOffsetX = 4;
  const float LampOffsetY = 12;
  const float GridStartX = 546;
  const float GridStartY = 218;
  const float LeftHUDColumn = 100;
  const float RightHUDColumn = 1734;
  const float HUDRow1 = 230;
  const float HUDRow2 = 322;
  const float HUDRow3 = 414;
  const float HUDRow4 = 506;
  const float HUDRow5 = 598;
  const float HUDRow6 = 690;
  const float HUDRow7 = 776;

  const std::string HintText =
      "Canoneer, remember!   Sol - Frag   Hev - HE   Air - Flak";
  const std::string Tutorial1Text =
      "Tutorial: arrows - aim, X - charge, Z - fire, C - "
      "change Type. Esc - "
      "exit. Aim at enemy coordinates, load charges";
  const std::string Tutorial2Text =
      "and make wind correction by reversing wind power multiplying"
      "it on distance and adding to aim";
  const std::string Tutorial3Text =
      "Get as many score as can in 120 seconds. H to hide tutorial. V to start/restart";
};
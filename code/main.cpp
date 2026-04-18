#include <cstdlib>
#include <ctime>

#include "assetManager.h"
#include "gamemode.h"

int main() {
  srand(time(NULL));

  sf::RenderWindow Window(sf::VideoMode::getDesktopMode(), "Canoneer",
                          sf::State::Fullscreen);

  AssetManager Manager = AssetManager();
  Gamemode GM(&Window, &Manager);

  while (Window.isOpen()) {
    while (auto event = Window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) Window.close();
    }
    GM.Tick();
  }
  return 0;
}
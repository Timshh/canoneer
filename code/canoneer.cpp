#include "gamemode.h"
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  sf::RenderWindow Window(sf::VideoMode({1920, 1080}), "Canoneer",
                          sf::State::Fullscreen);
  Gamemode GM(&Window);
  while (Window.isOpen()) {
    GM.Tick();
  }
  return 0;
}
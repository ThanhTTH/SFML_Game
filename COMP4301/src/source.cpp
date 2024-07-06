#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"

int main(int argc, char const *argv[]) {
  Game game;
  while (!game.GetWindow()->isDone()) {
    game.Update();
    game.Render();
    game.LateUpdate();
    
  }
  return 0;
}
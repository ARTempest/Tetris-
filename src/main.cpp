#include "../include/game.h"
#include "../include/render.h"
#include "../include/character.h"

int main() {
  Letter::initializeUmap(); 

  Game game(800, 600);
  game.Init();

  Render render(&game);
  render.activate();
}

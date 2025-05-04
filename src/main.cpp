#include "../include/game.h"
#include "../include/render.h"

int main() {
  Game game(800, 600);
  game.Init();

  Render render(&game);
  render.activate();
}

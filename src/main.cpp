#include "game/game.h"
#include "render/render.h"

int main() {
  Game game(800,600);
  game.Init();
  Render render(&game);
  render.loop();
}

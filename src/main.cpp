#include "../include/game.h"
#include "../include/render.h"
#include "../include/character.h"
#include "../include/music.h"

int main() {
  Letter::initializeUmap();
  
  if (!initMusic("../music/Tetris.mp3")) {
    return 1;
  };

  Game game(800, 600);
  game.Init();

  Render render(&game);
  render.activate();

  cleanupMusic();
}

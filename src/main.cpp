#include "game/game.h"
#include "../include/shader.h"
#include "render/render.h"
#include "block/block.h"

int main() {
  // Initializing Game Class
  Game game(800,600);
  game.Init();

  Shader myShader("../src/shaders/vShader.txt", "../src/shaders/fShader.txt");
  Block bk (glm::vec2(1.0f,1.0f), Block::blue);

  // Initializing Render Class
  Render render(&game, &myShader, &bk);
  render.loop();
}

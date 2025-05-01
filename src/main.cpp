#include "../include/game.h"
#include "../include/shader.h"
#include "../include/render.h"
#include "../include/texture.h"
#include "../include/block.h"
#include <glm/ext/vector_float2.hpp>

int main() {
  Game game(800, 600);
  game.Init();

  Shader blockShader("../src/shaders/block/vShader.txt", "../src/shaders/fShader.txt");
  Shader wallShader("../src/shaders/background/vShader.txt", "../src/shaders/fShader.txt");
  Shader placedBlockShader("../src/shaders/wall/vShader.txt", "../src/shaders/fShader.txt");

  Block block;
  Block wall;
  Block placedBlock;

  Texture myTexture("../textures/background.png");

  Render render(&game, &blockShader, &wallShader, &placedBlockShader,&block, &wall, &placedBlock, &myTexture);
  render.activate();
}

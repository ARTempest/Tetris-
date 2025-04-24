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

  Block block (glm::vec2(1.0f,1.0f), Block::blue);
  Block wall (glm::vec2(1.0f, 1.0f), Block::blue);

  Texture myTexture("../textures/background.png");

  Render render(&game, &blockShader, &wallShader, &block, &wall, &myTexture);
  render.activate();
}

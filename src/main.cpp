#include "../include/game.h"
#include "../include/shader.h"
#include "../include/render.h"
#include "../include/texture.h"
#include "../include/block.h"

int main() {
  Render* renderPointer;

  // Initializing Game Class
  Game game(800, 600);
  game.Init();

  Shader myShader("../src/shaders/vShader.txt", "../src/shaders/fShader.txt");
  Block myBlock (glm::vec2(1.0f,1.0f), Block::blue);
  Texture myTexture("../textures/blue_block.png");

  // Initializing Render Class
  Render render(&game, &myShader, &myBlock, &myTexture);
  renderPointer = &render;
  render.loop();
}

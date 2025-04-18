#include "../include/render.h"
#include "../include/game.h"
#include "../include/block.h"
#include "../include/piece.h"
#include "../include/shader.h"
#include "../include/texture.h"
#include <glm/ext/vector_float2.hpp>
#include <iostream>

Render::Render(Game* g, Shader* s, Block* b, Texture* t) {
  game   = g;
  shader = s;
  block  = b;
  texture= t;
}

void Render::loop() {

  while (!glfwWindowShouldClose(game->window)) {
    actualizeFrame();
    game->processInput(frame); // Input
    renderization(); // Rendering Commands
    swapBuffers(); // Calls and swap buffers
 }

  glDeleteVertexArrays(1, &block->VAO);
  glDeleteBuffers(1, &block->VBO);
  glDeleteBuffers(1, &block->EBO);
  glfwTerminate();
}

void Render::renderization(){
 // Define and Apply the Background
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT); 

  glm::mat4 projection = glm::ortho(0.0f, game->worldW, 0.0f, game->worldH, -1.0f, 1.0f);

  for (int i=0; i < 4; i++){
  
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(game->activePiece->blockPos[i], 0.0f));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->texture);

  shader->use();
  shader->setMat4("model", model);
  shader->setMat4("projection", projection);

  glBindVertexArray(block->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
 }

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}

void Render::actualizeFrame() {
  frame += 1;
  if (frame == 60) {
    frame = 0;
  }

  std::cout << frame << '\n';
}

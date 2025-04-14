#include "render.h"
#include "../game/game.h"
#include "../block/block.h"
#include "../../include/shader.h"
#include <GLFW/glfw3.h>


Render::Render(Game* g, Shader* s, Block* b) {
  game   = g;
  shader = s;
  block  = b;
}

void Render::loop() {
  while (!glfwWindowShouldClose(game->window)) {

    game->processInput(); // Input
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
  
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT); 
  shader->use();

  glBindVertexArray(block->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}



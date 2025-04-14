#include "render.h"
#include "../game/game.h"
#include "../block/block.h"
#include "../../include/shader.h"


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
}

void Render::renderization(){
 // Define and Apply the Background
  
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT); 

  // Define an orto projection
  //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 6.0f, 0.0f));
  //glm::mat4 projection = glm::ortho(0.0f, 10.0f, 20.0f, 0.0f, -1.0f, 1.0f);

  shader->use();
  glBindVertexArray(block->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}



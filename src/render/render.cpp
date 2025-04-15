#include "render.h"
#include "../game/game.h"
#include "../block/block.h"
#include "../../include/shader.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>


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

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 6.0f, 0.0f));
  glm::mat4 projection = glm::ortho(0.0f, 10.0f, 20.0f, 0.0f, -1.0f, 1.0f);

  
  
  shader->use();
  shader->setMat4("model", model);
  shader->setMat4("projection", projection);
  




  glBindVertexArray(block->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}



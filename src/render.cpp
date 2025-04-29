#include "../include/render.h"
#include "../include/game.h"
#include "../include/block.h"
#include "../include/shader.h"
#include "../include/texture.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>

Render::Render(Game* g, Shader* bs, Shader* ws, Block* b, Block* w, Texture* t) : 
  game(g),
  blockShader(bs),
  wallShader(ws),
  block(b),
  wall(w),
  wallTexture(t) {};

void Render::activate() {

  while (!glfwWindowShouldClose(game->window)) {
    actualizeFrame();
    game->processInput(frame); // Input
    renderization(); // Rendering Commands
    swapBuffers(); // Calls and swap buffers
 }

  glDeleteVertexArrays(1, &block->VAO);
  glDeleteBuffers(1, &block->VBO);
  glDeleteBuffers(1, &block->EBO);
  delete game->activePiece;
  glfwTerminate();
}

void Render::actualizeFrame() {
  frame += 1;
  if (frame == 60) {
    frame = 0;
  }
}

void Render::renderization(){
  
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT); 

  glm::mat4 projection = glm::ortho(0.0f, game->worldW, 0.0f, game->worldH, -1.0f, 1.0f);

  wallShader->use();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, wallTexture->get());
  glBindVertexArray(wall->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, game->activePiece->texture->get());

  for (int i=0; i < 4; i++){
  
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(game->activePiece->blockPos[i], 0.0f));

    blockShader->use();
    blockShader->setMat4("model", model);
    blockShader->setMat4("projection", projection);
    blockShader->setVec2("atlasScale", game->getAtlasScale());
    blockShader->setVec2("atlasOffset", game->activePiece->getAtlasOffset());

    glBindVertexArray(block->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}

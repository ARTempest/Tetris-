#include "../include/render.h"
#include "../include/game.h"
#include "../include/block.h"
#include "../include/shader.h"
#include "../include/texture.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>

Render::Render(Game* g, Shader* bs, Shader* ws, Shader* pbs,Block* b, Block* bg, Block* pb,Texture* t) : 
  game(g),
  blockShader(bs),
  wallShader(ws),
  placedBlockShader(pbs),
  block(b),
  background(bg),
  placedBlock(pb),
  wallTexture(t) {};

void Render::activate() {
  initPlacedBlocks();


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
  glBindVertexArray(background->VAO);
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

  if (game->needUpdate == true) {
    actualizePlacedBlocks();
    game->needUpdate = false;
  }


  placedBlockShader->use();
  placedBlockShader->setMat4("projection", projection);

  glBindVertexArray(placedBlock->VAO);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, game->placedBlocks.size());

}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}


void Render::initPlacedBlocks() {
  glGenBuffers(1, &instanceVBO);
}

void Render::actualizePlacedBlocks() {
  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * game->placedBlocks.size(), game->placedBlocks.data(), GL_STATIC_DRAW);

  glBindVertexArray(placedBlock->VAO);

  std::size_t vec4Size = sizeof(glm::vec4);

  for (unsigned int i=0; i < 4; i++) {
    unsigned int location = 2+i;

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
    glVertexAttribDivisor(location, 1);
  } 

}



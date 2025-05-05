#include "../include/render.h"
#include "../include/game.h"
#include "../include/shader.h"
#include "../include/texture.h"
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>

Render::Render(Game*g) : game(g) {};

void Render::activate() {
  initPlacedBlocks();

  while (!glfwWindowShouldClose(game->window)) {
    actualizeFrame();
    game->processInput(frame);  // Input
    renderization();            // Rendering Commands
    swapBuffers();              // Calls and swap buffers
 }

  glDeleteVertexArrays(1, &block.VAO);
  glDeleteBuffers(1, &block.VBO);
  glDeleteBuffers(1, &block.EBO);
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

  drawBackground();
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, game->activePiece->texture->get());

  drawActiveBlocks(projection);

  checkPlacedBlocksUpdate();
  
  drawPlacedBlocks(projection);

  drawNumbers(projection);
  drawLetters(projection);
}

void Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(game->window);
}

void Render::drawActiveBlocks(glm::mat4 projection) {
  for (int i=0; i < 4; i++){
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(game->activePiece->blockPos[i], 0.0f));

    blockShader.use();
    blockShader.setMat4("model", model);
    blockShader.setMat4("projection", projection);
    blockShader.setVec2("atlasScale", game->getAtlasScale());
    blockShader.setVec2("atlasOffset", game->activePiece->getAtlasOffset());

    glBindVertexArray(block.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

void Render::drawPlacedBlocks(glm::mat4 projection) {
  placedBlockShader.use();
  placedBlockShader.setMat4("projection", projection);
  placedBlockShader.setVec2("atlasScale", game->getAtlasScale());

  glBindVertexArray(placedBlock.VAO);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, game->placedBlocks.size());
}

void Render::drawBackground() {
  backgroundShader.use();
 
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, wallTexture.get());
  glBindVertexArray(background.VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::drawNumbers(glm::mat4 projection) {
  blockShader.use();
  blockShader.setMat4("projection", projection);
  blockShader.setVec2("atlasScale", game->getAtlasScale());
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, numbersTexture.get());
  glBindVertexArray(block.VAO);

  for (Number number: game->numbers) {
    blockShader.setMat4("model", number.model);
    blockShader.setVec2("atlasOffset", number.texCoords);

    glBindVertexArray(block.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

void Render::drawLetters(glm::mat4 projection) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, lettersTexture.get());
  glBindVertexArray(block.VAO);

  for (Letter letter: game->letters) {
    blockShader.setMat4("model", letter.model);
    blockShader.setVec2("atlasOffset", letter.texCoords);

    glBindVertexArray(block.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

}


void Render::initPlacedBlocks() {
  glGenBuffers(1, &instancePlacedVBO);
}

void Render::checkPlacedBlocksUpdate() {
  if (game->needUpdate == true) {
    updatePlacedBlocks();
    game->needUpdate = false;
  }
}


void Render::updatePlacedBlocks() {
  glBindBuffer(GL_ARRAY_BUFFER, instancePlacedVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(PlacedBlock) * game->placedBlocks.size(), game->placedBlocks.data(), GL_DYNAMIC_DRAW);

  glBindVertexArray(placedBlock.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, instancePlacedVBO);

  std::size_t vec4Size = sizeof(glm::vec4);
  std::size_t stride = sizeof(PlacedBlock);

  for (unsigned int i=0; i < 4; i++) {
    unsigned int location = 2+i;

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, stride, (void*)(i * vec4Size));
    glVertexAttribDivisor(location, 1);
  }

  unsigned int offsetLoc = 6;
  glEnableVertexAttribArray(offsetLoc);
  glVertexAttribPointer(offsetLoc, 2, GL_FLOAT, GL_FALSE, stride, (void*)( sizeof(glm::mat4)));
  glVertexAttribDivisor(offsetLoc, 1);
}

void Render::initScoreBlocks() {
  glGenBuffers(1, &instanceScoreVBO);
}



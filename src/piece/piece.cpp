#include "piece.h"  // T L J S Z O
#include "../block/block.h"
#include <glm/ext/vector_float2.hpp>

Piece::Piece(shape newShape, glm::vec2 pos) {
// Selecting piece shape

  switch (newShape) {
    case Piece::T:
      createT(pos);
      break;

    case Piece::L:
      createL(pos);
      break;

    case Piece::J:
      createJ(pos);
      break;

    case Piece::S:
      createS(pos);
      break;

    case Piece::Z:
      createZ(pos);
      break;

    default:
      createO(pos);
      break;
  }
};

void Piece::createT(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x - 2, pos.y + 2};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x + 2, pos.y + 2};
}

void Piece::createL(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x + 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x, pos.y + 4};

}

void Piece::createJ(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x - 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x, pos.y + 4};
}

void Piece::createS(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x - 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x + 2, pos.y + 2};
}

void Piece::createZ(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x + 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x - 2, pos.y + 2};
}

void Piece::createO(glm::vec2 pos) {
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x + 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x + 2, pos.y + 2};
}


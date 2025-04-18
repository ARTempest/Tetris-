#include "../include/piece.h"  // T L J S Z I O
#include "../include/block.h"
#include <glm/ext/vector_float2.hpp>

Piece::Piece(shapes newShape, glm::vec2 pos) {
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

    case Piece::I:
      createI(pos);
    break;
    default:
      createO(pos);
    break;
  }
};

void Piece::createT(glm::vec2 pos) {
  shape = Piece::T;
  
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y - 2};
  blockPos[2] = {pos.x - 2, pos.y};
  blockPos[3] = {pos.x + 2, pos.y};

  amountRot = 4;
  blockRot[0] = {glm::vec2(0,-2), glm::vec2(-2,0) , glm::vec2(2,0)};
  blockRot[1] = {glm::vec2(0,-2), glm::vec2(-2,0) , glm::vec2(0,2)};
  blockRot[2] = {glm::vec2(2,0) , glm::vec2(-2,0) , glm::vec2(0,2)};
  blockRot[3] = {glm::vec2(2,0) , glm::vec2(0,-2) , glm::vec2(0,2)};
}

void Piece::createL(glm::vec2 pos) {
  shape = Piece::L;
  
  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y + 2};
  blockPos[2] = {pos.x, pos.y - 2};
  blockPos[3] = {pos.x + 2, pos.y - 2};

  amountRot = 4;
  blockRot[0] = {glm::vec2(0,2), glm::vec2(0,-2), glm::vec2(2,-2)};
  blockRot[1] = {glm::vec2(-2,0), glm::vec2(2,0), glm::vec2(2,2)};
  blockRot[2] = {glm::vec2(0,-2), glm::vec2(0,2), glm::vec2(-2,2)};
  blockRot[3] = {glm::vec2(2,0), glm::vec2(-2,0), glm::vec2(-2,-2)};
}

void Piece::createJ(glm::vec2 pos) {
  shape = Piece::J;

  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y - 2};
  blockPos[2] = {pos.x - 2, pos.y - 2};
  blockPos[3] = {pos.x, pos.y + 2};

  amountRot = 4;
  blockRot[0] = {glm::vec2(0,-2), glm::vec2(-2,-2), glm::vec2(0,2)};
  blockRot[1] = {glm::vec2(-2,0), glm::vec2(-2,2), glm::vec2(2,0)};
  blockRot[2] = {glm::vec2(0,2), glm::vec2(2,2), glm::vec2(0,-2)};
  blockRot[3] = {glm::vec2(2,0), glm::vec2(2,-2), glm::vec2(-2,0)};
}

void Piece::createS(glm::vec2 pos) {
  shape = Piece::S;

  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y - 2};
  blockPos[2] = {pos.x - 2, pos.y - 2};
  blockPos[3] = {pos.x + 2, pos.y};


  amountRot = 2;
  blockRot[0] = {glm::vec2(0,-2), glm::vec2(-2,-2), glm::vec2(2,0)};
  blockRot[1] = {glm::vec2(2,0), glm::vec2(2,-2), glm::vec2(0,2)};
}

void Piece::createZ(glm::vec2 pos) {
  shape = Piece::Z;

  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y - 2};
  blockPos[2] = {pos.x + 2, pos.y - 2};
  blockPos[3] = {pos.x - 2, pos.y};
  
  amountRot = 2;
  blockRot[0] = {glm::vec2(0,-2), glm::vec2(2,-2), glm::vec2(-2,0)};
  blockRot[1] = {glm::vec2(2,0), glm::vec2(2,2), glm::vec2(0,-2)};
}

void Piece::createI(glm::vec2 pos) {
  shape = Piece::I;

  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x, pos.y + 2};
  blockPos[2] = {pos.x, pos.y + 4};
  blockPos[3] = {pos.x, pos.y - 2}; 

  amountRot = 2;
  blockRot[0] = {glm::vec2(0,2), glm::vec2(0,4), glm::vec2(0,-2)};
  blockRot[1] = {glm::vec2(-2,0), glm::vec2(-4,0), glm::vec2(2,0)};
}

void Piece::createO(glm::vec2 pos) {
  shape = Piece::O;

  blockPos[0] = {pos.x, pos.y};
  blockPos[1] = {pos.x + 2, pos.y};
  blockPos[2] = {pos.x, pos.y + 2};
  blockPos[3] = {pos.x + 2, pos.y + 2};
}

void Piece::move(int x, int y) {
  for (auto& pos: blockPos) {
    pos.x += x;
    pos.y += y;
  }
}

void Piece::rotate(int dir) {

  if (shape != Piece::O) {
    numberRot += dir;

    if (numberRot < 0) {
      numberRot = amountRot - 1;
    }
    else if (numberRot > amountRot - 1) {
      numberRot = 0;
    }

    for (int i=0; i <= 2; i++) {
      blockPos[i + 1] = blockPos[0] + blockRot[numberRot][i];
    }
  }
}




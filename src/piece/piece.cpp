#include "piece.h"  // T L J S Z O
#include <glm/fwd.hpp>


Piece::Piece(shape newShape, float posX){
// Selecting piece shape
  switch (newShape) {
    case Piece::T:
      createT();
      break;

    case Piece::L:
      createL();
      break;

    case Piece::J:
      createJ();
      break;

    case Piece::S:
      createS();
      break;

    case Piece::Z:
      createZ();
      break;

    default:
      createO();
      break;
  }

// Assigning a position for the new piece
  position.x = posX;
};




#pragma once
#ifndef PLACED_BLOCK_H
#define PLACED_BLOCK_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>

struct PlacedBlock {
  glm::mat4 model;
  glm::vec2 textureCoord;
  glm::vec2 boardCoords;
};

#endif



#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <iostream>

#include <unordered_map>

struct Character {
  glm::mat4 model;
  glm::vec2 texCoords;
};

struct Letter : Character {
  enum letter{s,c,o,r,e,l,i,n};
  static std::unordered_map<letter, glm::vec2> umap;
  static void initializeUmap();


  Letter() {
    model = glm::mat4(1.0);
    texCoords = glm::vec2(0,0);
  }

  Letter(letter value, glm::mat4 newModel) {
    
    model = newModel;
    texCoords = umap[value];
  }


};

struct Number : Character {
  static glm::vec2 numbers[10];

  Number(){
    model = glm::mat4(1.0);
    texCoords = glm::vec2(0,0);
  }

  Number(int value, glm::mat4 newModel) {
    model = newModel;
    
    if (value < 0 || value > 9) {
      std::cout << "Invalid number index: " << value << '\n';
      texCoords = glm::vec2(0.0f); // fallback
    } else {
    texCoords = numbers[value];
    }
  }
};
#endif


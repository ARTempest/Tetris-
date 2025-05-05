#include "../include/character.h"
#include <glm/ext/vector_float2.hpp>
#include <unordered_map>

std::unordered_map<Letter::letter, glm::vec2> Letter::umap;

glm::vec2 Number::numbers[10] = {
    glm::vec2(1, 2), glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(2, 0),
    glm::vec2(3, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(2, 1),
    glm::vec2(3, 1), glm::vec2(0, 2)
};

void Letter::initializeUmap() {
  umap[Letter::s] = glm::vec2(0,0);
  umap[Letter::c] = glm::vec2(1,0);
  umap[Letter::o] = glm::vec2(2,0);
  umap[Letter::r] = glm::vec2(3,0);

  umap[Letter::e] = glm::vec2(0,1);
  umap[Letter::l] = glm::vec2(1,1);
  umap[Letter::i] = glm::vec2(2,1);
  umap[Letter::n] = glm::vec2(3,1);
}



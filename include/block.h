#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Block {
private:
  glm::vec3 color;

  const float vertices[20] = {
     // Position               // Texture
     1.0f,  1.0f, 0.0f,      0.0f, 1.0f, // top right
     1.0f, -1.0f, 0.0f,      0.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f,      1.0f, 0.0f, // bottom left
    -1.0f,  1.0f, 0.0f,      1.0f, 1.0f  // top left 
  };

  const int indices[6] = {
    0, 1, 3,
    1, 2, 3
  };


public:
  unsigned int VBO, VAO, EBO;
  glm::vec2 position;
  enum colors {red, blue, yellow, green};

  Block(glm::vec2, colors);
};

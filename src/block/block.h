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
  unsigned int VBO, VAO, BEO;
  glm::vec3 color;
public:
  glm::vec2 position;
  enum colors {red, blue, yellow, green};

  Block(glm::vec2, colors);
};

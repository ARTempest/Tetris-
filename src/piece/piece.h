#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Piece {
private:
  const float posY = 7.0f;
  const float posZ = 0.0f;
public:
  enum shape {T, L, J, S, Z, O};
  glm::vec3 position = glm::vec3(0, posY, posZ);
  Piece(shape, float);
  void createT();
  void createL();
  void createJ();
  void createS();
  void createZ();
  void createO();
};






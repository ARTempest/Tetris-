#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {

public:
  unsigned int ID;
    
  Shader(const char*, const char*);
    
  void use();

  void setBool(const std::string &, bool) const;
  void setInt(const std::string &, int) const;
  void setFloat(const std::string &, float) const;
  void setVec2(const std::string &, glm::vec2) const;
  void setMat4(const std::string &, glm::mat4) const;
};

#endif

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {

public:
  unsigned int ID;
    
  Shader(const char*, const char*);
    
  void use();

  void setBool(const std::string &, bool) const;
  void setInt(const std::string &, int) const;
  void setFloat(const std::string &, float) const;
};

#endif

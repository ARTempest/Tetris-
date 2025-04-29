#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../libs/stb_image.h"

class Texture {
private:
  int width, height, nrChannels;
  unsigned int texture;
  unsigned char *data; 
public:
  Texture(const char*);
  unsigned int get();
};
#endif


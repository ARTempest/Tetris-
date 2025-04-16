#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../libs/stb_image.h"


class Texture {
private:
  int width, height, nrChannels;
public:
  unsigned int texture;
  unsigned char *data; 
  Texture(const char*);
};

#endif


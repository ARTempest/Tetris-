#include "texture.h"


Texture::Texture(const char* path) {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



  data = stbi_load(path, &width, &height, &nrChannels, 0);

  if (data) {

    GLenum format = GL_RGB;
    
    if (nrChannels == 4) {
        format = GL_RGBA;
    } else if (nrChannels == 1) {
        format = GL_RED;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "FAILED TO LOAD TEXTURE" << '\n';
  }

  stbi_image_free(data);
}

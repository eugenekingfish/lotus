#include "vshader.h"
#include <fstream>
#include <iostream>
#include <GL/glew.h>

vshader::vshader(const char* path) {
   this->path = path;
}

std::string vshader::read_source() const {

   std::ifstream file(this->path);

   if (!file.is_open())
   {
      std::cerr << "Could not open the file: " << this->path << std::endl;
      exit(EXIT_FAILURE);
   }

   return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void vshader::init() const {

   GLuint shader = glCreateShader(GL_VERTEX_SHADER);
   const char* source = this->read_source().c_str();
   glShaderSource(shader, 1, &source, NULL);
}

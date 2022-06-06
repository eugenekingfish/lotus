#include "shader.h"
#include <GL/glew.h>

shader::shader(const char* frag_path, const char* vert_path) {
   this->frag_path = frag_path;
   this->vert_path = vert_path;
}

std::string shader::read_source(const char* path) const {
   std::ifstream file(path);

   if (!file.is_open())
   {
      std::cerr << "Could not open the file: " << path << std::endl;
      exit(EXIT_FAILURE);
   }

   return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void shader::get_log() const
{
}

GLuint shader::init() {

   const char* frag_source = this->read_source(this->frag_path).c_str();
   const char* vert_source = this->read_source(this->vert_path).c_str();

   GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
   GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(v_shader, 1, &vert_source, NULL);
   glShaderSource(f_shader, 1, &frag_source, NULL);

   glCompileShader(v_shader);
   glCompileShader(f_shader);

   GLuint vf_program = glCreateProgram();

   glAttachShader(vf_program, v_shader);
   glAttachShader(vf_program, f_shader);

   glLinkProgram(vf_program);

   return vf_program;
}

GLuint shader::get_shader() const {
   return this->_shader;
}

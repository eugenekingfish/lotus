#include "shader.h"
#include <GL/glew.h>

shader::shader(const char* frag_path, const char* vert_path) {
   this->frag_path = frag_path;
   this->vert_path = vert_path;
}

std::string shader::read_source(const char* path) {

   std::string file_content;
   std::ifstream file(path, std::ios::in);
   std::string line = "";

   while (!file.eof()) {
      getline(file, line);
      file_content.append(line + '\n');
   }
   file.close();
   return file_content;
}

void shader::print_log(GLuint shader) const {

   int length = 0;
   int char_written = 0;
   char* log;

   glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

   if (length > 0) {
      log = (char*)malloc(length);
      glGetShaderInfoLog(shader, length, &char_written, log);
      std::cout << "Shader Log: " << log << std::endl;
      free(log);
   }
}

bool shader::check_gl_error() const {

   bool error_found = false;
   int gl_error = glGetError();

   while (gl_error != GL_NO_ERROR) {
      std::cout << "gl_error: " << gl_error << std::endl;
      error_found = true;
      gl_error = glGetError();
   }
   return error_found;
}


GLuint shader::init() {

   GLint vert_compiled, frag_compiled;

   std::string v_string = read_source(vert_path);
   
   const char* vert_source = v_string.c_str();
   
   const char* frag_source = 
		"#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

   GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
   GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(v_shader, 1, &vert_source, NULL);
   glCompileShader(v_shader);

   // Checking that the vertex shader successfully compiles.
   check_gl_error();
   glGetShaderiv(v_shader, GL_COMPILE_STATUS, &vert_compiled);

   if (vert_compiled != 1) {
      std::cout << "ERROR: Vertex shader compilation failed." << std::endl;
      print_log(v_shader);
   }

   glShaderSource(f_shader, 1, &frag_source, NULL);
   glCompileShader(f_shader);
   
   // Checking that the fragment shader successfully compiles. 
   check_gl_error();
   glGetShaderiv(f_shader, GL_COMPILE_STATUS, &frag_compiled);

   if (frag_compiled != 1) {
      std::cout << "ERROR: Fragment shader compilation failed." << std::endl;
      print_log(f_shader);
   }

   GLuint vf_program = glCreateProgram();

   glAttachShader(vf_program, v_shader);
   glAttachShader(vf_program, f_shader);

   glLinkProgram(vf_program);

   return vf_program;
}


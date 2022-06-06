#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

class shader {
   private:
      const char* frag_path;
      const char* vert_path;
      GLuint _shader;
      std::string read_source(const char* path) const;

   public:
      shader(const char* frag_path, const char* vert_path);
      GLuint init();
      GLuint get_shader() const;
      void get_log() const;

};

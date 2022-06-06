#include<string>

class vshader {
   private:
      const char* path; // Path to the shader's source code
      std::string read_source() const; // Read's the shader's source code and returns it as a string.

   public:
      vshader(const char* path);
      void init() const;

};

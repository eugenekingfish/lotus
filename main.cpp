#include "vshader.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>


#define num_vaos 1 

using namespace std;

GLuint rendering_program; 
GLuint vao[num_vaos]; 

GLuint createShaderProgram() {
const char *fshaderSource =
   "#version 430 \n"
   "out vec4 color; \n"
   "void main(void) \n"
   "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

   GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

   vshader v("vert.txt");
   v.init();

   glShaderSource(fShader, 1, &fshaderSource, NULL);

   glCompileShader(fShader);

   GLuint vfProgram = glCreateProgram();

   glAttachShader(vfProgram, fShader);

   glLinkProgram(vfProgram);
   
   return vfProgram;
}

void initialise(GLFWwindow* window) {
   rendering_program = createShaderProgram();
   glGenVertexArrays(num_vaos, vao);
   glBindVertexArray(vao[0]);
}
void display(GLFWwindow* window, double currentTime) {
   glUseProgram(rendering_program);
   glDrawArrays(GL_POINTS, 0, 1);
}
int main(void) {
   if (!glfwInit()) { exit(EXIT_FAILURE); }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   GLFWwindow* window = glfwCreateWindow(1280, 720, "Window", NULL, NULL);
   glfwMakeContextCurrent(window);

   if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

   glfwSwapInterval(1);
   initialise(window);

   while (!glfwWindowShouldClose(window)) {
          display(window, glfwGetTime());
         glfwSwapBuffers(window);
         glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   exit(EXIT_SUCCESS);
}

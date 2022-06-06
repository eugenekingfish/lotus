#include "shader.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>


#define num_vaos 1 

using namespace std;

GLuint rendering_program; 
GLuint vao[num_vaos]; 


void initialise(GLFWwindow* window) {
   shader s("frag.txt", "vert.txt");
   rendering_program = s.init();
   glGenVertexArrays(num_vaos, vao);
   glBindVertexArray(vao[0]);
}
void display(GLFWwindow* window, double currentTime) {
   glClearColor(1.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glUseProgram(rendering_program);
   glPointSize(30.0f);
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

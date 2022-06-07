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

GLuint create_shader_program() {
      const char *vshaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
      const char *fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
      GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
      GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(vShader, 1, &vshaderSource, NULL);
      glShaderSource(fShader, 1, &fshaderSource, NULL);
      glCompileShader(vShader);
      glCompileShader(fShader);
      GLuint vfProgram = glCreateProgram();
      glAttachShader(vfProgram, vShader);
      glAttachShader(vfProgram, fShader);
      glLinkProgram(vfProgram);
      return vfProgram;
}

void initialise(GLFWwindow* window) {
   shader s("frag.txt", "vert.txt");
   //rendering_program = create_shader_program();
   rendering_program = s.init();
   glGenVertexArrays(num_vaos, vao);
   glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
   glUseProgram(rendering_program);
   glClearColor(1.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glPointSize(100.0f);
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

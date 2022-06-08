#include "shader.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include "glm/glm/glm.hpp"
#include "glm/glm/ext.hpp"


using namespace std;

#define num_vaos 1 
#define num_vbos 2


GLuint rendering_program; 

glm::vec3 camera_pos;
glm::vec3 cube_pos;

GLuint vao[num_vaos]; 
GLuint vbo[num_vbos]; 

GLuint mv_loc, proj_loc;
int width, height;
float aspect;
glm::mat4 p_mat, v_mat, m_mat, mv_mat;

class window {
   public:
      GLFWwindow* window_ptr;
      window(const int& size_x, const int& size_y, const char* window_title) {
         if (!glfwInit()) {
            std::cout << "Failed to initialise GLFW." << std::endl;
            exit(EXIT_FAILURE); 
         }
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
         this->window_ptr = glfwCreateWindow(size_x, size_y, window_title, NULL, NULL);
      }

      void init() {
         glfwMakeContextCurrent(window_ptr);
         if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
         glfwSwapInterval(1); // sets the color buffer swap interval (i.e. vsync)
      }

      void destroy() {
         glfwDestroyWindow(window_ptr);
         glfwTerminate();
      }

};

void init_vertices() {
   float vertex_positions[108] = {
      -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
   };
   

   glGenVertexArrays(1, vao); 
   glBindVertexArray(vao[0]);
   glGenBuffers(num_vbos, vbo);

   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
}

void display(GLFWwindow* window, double currentTime) {
   glClear(GL_DEPTH_BUFFER_BIT);
   glUseProgram(rendering_program);
   
   // building the perspective matrix
   mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
   proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");

   glfwGetFramebufferSize(window, &width, &height);
   aspect = (float)width / (float)height;
   p_mat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

   // building the view, model, and model-view matrices

   v_mat = glm::translate(glm::mat4(1.0f), -camera_pos);
   m_mat = glm::translate(glm::mat4(1.0f), cube_pos);
   mv_mat = v_mat * m_mat;

   glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv_mat));
   glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));

   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDrawArrays(GL_TRIANGLES, 0, 36);
}
int main(void) {
   camera_pos = {0.0f, 0.0f, 8.0f};
   cube_pos = {0.0f, -2.0f, 0.0f};

   window w(1280, 720, "Hello");

   w.init();
   init_vertices();

   shader s("frag.txt", "vert.txt");
   rendering_program = s.init();


   while (!glfwWindowShouldClose(w.window_ptr)) {
      display(w.window_ptr, glfwGetTime());
      glfwSwapBuffers(w.window_ptr); // swaps the front and back color buffers
      glfwPollEvents();
   }

   w.destroy();

   exit(EXIT_SUCCESS);
}

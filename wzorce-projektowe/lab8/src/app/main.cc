#include <iostream>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GL/gl.h>

#include <GLFW/glfw3.h>

#include "Application.hpp"

static void glfw_error_callback(int error, const char * description) {
  std::cerr << "GLFW Error " << error << ": " << description << '\n';
}

int main(int argc, char ** argv, char ** env) {
  // Set glfw error callback and inintialise glfw
  glfwSetErrorCallback(glfw_error_callback);
  if(!glfwInit())
    return 1;

  // GL 3.0 + GLSL 130
  const char * glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create a window with graphics context
  GLFWwindow * window = glfwCreateWindow(800, 600,
					 "Command+Memento",
					 NULL, NULL);
  if(window == NULL)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO & io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Our state
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Application backbone
  Application & application = Application::getInstance();
  const uint numberOfWindows = argc>1 ? std::atoi(argv[1]) : 2;
  for(int i=0; i<numberOfWindows; ++i) {
    std::string windowName = "Window " + std::to_string(i+1);
    application.addBoxWindow(windowName.c_str());
  }

  // Main loop
  while(!glfwWindowShouldClose(window)) {
    // Poll and handle events
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Application's windows
    application.showWindows();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x*clear_color.w,
		 clear_color.y*clear_color.w,
		 clear_color.z*clear_color.w,
		 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

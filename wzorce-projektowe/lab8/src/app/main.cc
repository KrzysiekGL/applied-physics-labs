#include <GL/gl.h>
#include <cstdio>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

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
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  while(!glfwWindowShouldClose(window)) {
    // Poll and handle events
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window
    if(show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a smiple window that we create ourselves. Use Begin/End pair
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, World!");

      ImGui::Text("This is some useful text.");

      ImGui::Checkbox("Demo Window", &show_demo_window);

      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

      ImGui::ColorEdit3("clear color", (float*)&clear_color);

      if(ImGui::Button("Button"))
	counter++;

      ImGui::SameLine();
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		  1000.f/io.Framerate, io.Framerate);
      ImGui::End();
    }

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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>


void ShowToolBoxWindow()
{
	ImGui::Begin("Sample Window");
	ImGui::Text("Hi");
	ImGui::SetItemTooltip("Hello");

	// Add a button
	if (ImGui::Button("Click Me!"))
	{
		std::cout << "Button Clicked!" << std::endl;
	}
	ImGui::SetItemTooltip("This is a button");


	// End the window
	ImGui::End();
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Dialogue Fancifier", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);         
	ImGui_ImplOpenGL3_Init();


	// render loop
	while (!glfwWindowShouldClose(window))
	{
		bool show = true;
		bool showDemoWindow = false;
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport();
		ImGui::ShowDemoWindow(); 
		ShowToolBoxWindow();

		ImGui::Begin("Options");
		if(ImGui::Button("Show Demo Window")) 
		{
			showDemoWindow = true;
		}


		if(showDemoWindow)
		{
			ImGui::ShowDemoWindow();
		}
		ImGui::End();


		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		// Rendering
		// (Your code clears your framebuffer, renders your other stuff etc.)
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// (Your code calls glfwSwapBuffers() etc.)

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
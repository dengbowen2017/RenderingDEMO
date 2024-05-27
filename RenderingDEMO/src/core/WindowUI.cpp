#include "WindowUI.h"

namespace RenderingDEMO
{
	WindowUI::~WindowUI()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void WindowUI::Initialize(GLFWwindow* window)
	{
		m_Window = window;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		//set glsl version
		ImGui_ImplOpenGL3_Init("#version 130");
	}
	void WindowUI::ShowWindowUI()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(&m_MenuWindowOpen);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void WindowUI::OnUpdate()
	{

	}
}
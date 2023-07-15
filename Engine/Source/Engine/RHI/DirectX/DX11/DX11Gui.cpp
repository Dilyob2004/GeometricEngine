#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>

static bool DockSpaceOpen = true;
bool DX11DynamicRHI::RHICreateGUI(void* HandleWindow)
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}


	io.Fonts->AddFontFromFileTTF("../../Content/Font/Roboto-Bold.ttf", 20);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("../../Content/Font/Roboto-Regular.ttf", 20);

	ImGui_ImplWin32_Init(HandleWindow);
	ImGui_ImplDX11_Init(DXDevice, DXDeviceContext);



	ImGui::GetStyle().WindowPadding = ImVec2(15, 15);
	ImGui::GetStyle().WindowRounding = 5.0f;
	ImGui::GetStyle().FramePadding = ImVec2(5, 5);
	//ImGui::GetStyle().FrameRounding = 7.0f;
	ImGui::GetStyle().ItemSpacing = ImVec2(13, 13);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(8, 6);
	ImGui::GetStyle().IndentSpacing = 25.0f;
	ImGui::GetStyle().ScrollbarSize = 15.0f;
	ImGui::GetStyle().ScrollbarRounding = 9.0f;
	//ImGui::GetStyle().GrabMinSize = 5.0f;
	//ImGui::GetStyle().GrabRounding = 3.0f;


	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.09f, 0.09f, 0.09f, 1.0f };
	/// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	/// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.0f, 112.f/255.f, 224/255.f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };


	/// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	/// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	/// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	return true;
}
void DX11DynamicRHI::RHIBeginFrameGUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();		


	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
	ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &DockSpaceOpen, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	}

	ImGui::End();

}
void DX11DynamicRHI::RHIEndFrameGUI()
{
	ImGui::Render();



	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

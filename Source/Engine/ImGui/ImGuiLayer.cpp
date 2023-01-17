#include <Engine/Core/Application.h>
//#include <Editor/Editor.h>
#include <Engine/ImGui/ImGuiLayer.h>
#include <Engine/System/Time.h>
#include <Engine/MaterialDesign.inl>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_internal.h>
#include <Engine/IconsMaterialDesignIcons.h>
#include <Engine/ImGui/ImGuiRenderer.h>
namespace MeteorEngine
{
	ImGuiRenderer* renderer = NULL;
    LRESULT WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
    }
    ImGuiLayer::ImGuiLayer():
        Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {

    }
	void ImGuiLayer::OnEnableHighDpi()
	{
		ImGui_ImplWin32_EnableDpiAwareness();
	}
	void SetDarkThemeColors()
	{

		ImGui::GetStyle().WindowPadding = ImVec2(15, 15);
		ImGui::GetStyle().WindowRounding = 5.0f;
		ImGui::GetStyle().FramePadding = ImVec2(5, 5);
		ImGui::GetStyle().FrameRounding = 4.0f;
		ImGui::GetStyle().ItemSpacing = ImVec2(13, 13);
		ImGui::GetStyle().ItemInnerSpacing = ImVec2(8, 6);
		ImGui::GetStyle().IndentSpacing = 25.0f;
		ImGui::GetStyle().ScrollbarSize = 15.0f;
		ImGui::GetStyle().ScrollbarRounding = 9.0f;
		ImGui::GetStyle().GrabMinSize = 5.0f;
		ImGui::GetStyle().GrabRounding = 3.0f;


		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.09, 0.09, 0.09, 1.0f };
		/// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		/// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
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
	}
	void ImGuiLayer::DrawElem3Controls(const std::string& label, Vector3f& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}
    void ImGuiLayer::OnAttach()
    {

		/**uint32_t extensions_count = 0;

		std::vector<const char*> requiredExtentions;

		requiredExtentions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		requiredExtentions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
		SetupVulkan(requiredExtentions.data(), requiredExtentions.size());
		wd = &g_MainWindowData;
		VkSurfaceKHR surface = CreateSurface(Application::GetInstance().GetWindow().GetWindowPtr());
		SetupVulkanWindow(wd, surface, Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight());
		*/


		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;           // Enable Docking
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		ImGui_ImplWin32_Init(Application::GetInstance().GetWindow().GetWindowPtr());
		renderer =ImGuiRenderer::Create({ Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight() }, true);
    }
    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    void ImGuiLayer::OnBegin()
    {
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame(); {

			ImGui::Begin("Hello, world!");
			ImGui::End();
		}
		/**if (g_SwapChainRebuild)
		{
			int width = Application::GetInstance().GetWidth(), height = Application::GetInstance().GetHeight();
			if (width > 0 && height > 0)
			{
				ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
				ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData, g_QueueFamily, g_Allocator, width, height, g_MinImageCount);
				g_MainWindowData.FrameIndex = 0;
				g_SwapChainRebuild = false;
			}
		}

		// Start the Dear ImGui frame
		ImGui::NewFrame();

		{
		}*/


    }
    void ImGuiLayer::OnEnd()
    {
		renderer->Render();
		/// Rendering
		/**ImGui::Render();
		ImDrawData* main_draw_data = ImGui::GetDrawData();
		const bool main_is_minimized = (main_draw_data->DisplaySize.x <= 0.0f || main_draw_data->DisplaySize.y <= 0.0f);
		wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
		wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
		wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
		wd->ClearValue.color.float32[3] = clear_color.w;
		if (!main_is_minimized)
			FrameRender(wd, main_draw_data);

		// Update and Render additional Platform Windows
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		// Present Main Platform Window
		if (!main_is_minimized)
			FramePresent(wd);*/
    }

    void ImGuiLayer::OnTick()
    {
		ImGui::GetIO().DisplaySize = ImVec2((f32)Application::GetInstance().GetWidth(), (f32)Application::GetInstance().GetHeight());

	}
    void ImGuiLayer::OnEvent(Event &event)
    {
        ImGuiIO& io = ImGui::GetIO();
        if(io.WantCaptureKeyboard)
        {
        }

    }
}

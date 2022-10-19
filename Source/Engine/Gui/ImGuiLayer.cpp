#include <Engine/Core/Application.h>
#include <Editor/Editor.h>
#include <Engine/Gui/ImGuiLayer.h>
#include <Engine/System/Time.h>
#include <Engine/MaterialDesign.inl>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_internal.h>
#include <Engine/IconsMaterialDesignIcons.h>
namespace MeteorEngine
{
    LRESULT WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
		return 0;///ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
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
        ImGui::CreateContext();
		SetDarkThemeColors();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
		
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

		io.Fonts->AddFontFromFileTTF("Assets/Font/OpenSans-Bold.ttf", 20);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Font/OpenSans-Regular.ttf", 20);
		ImGui_ImplWin32_Init(Application::GetInstance().GetWindow().GetWindowPtr());

		static const ImWchar icons_ranges[] = { 0x30, 0xFE7D, 0 };
		ImFontConfig icons_config;
		// merge in icons from Font Awesome
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.GlyphOffset.y = 4.0f;
		icons_config.OversampleH = icons_config.OversampleV = 1;
		icons_config.GlyphMinAdvanceX = 4.0f;
		icons_config.SizePixels = 12.0f;

		io.Fonts->AddFontFromMemoryCompressedTTF(MaterialDesign_compressed_data, MaterialDesign_compressed_size, 26, &icons_config, icons_ranges);

    }
    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    void ImGuiLayer::OnBegin()
    {
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        bool p_open = true;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
        ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &p_open, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {

				if (ImGui::MenuItem("New")) {

				}
				if (ImGui::MenuItem("Open")) {

				}
				if (ImGui::MenuItem("Save")) {

				}

				if (ImGui::MenuItem("Save as..")) {

				}
                if (ImGui::MenuItem("Exit")) 
					Application::GetInstance().Close();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Settings"))
                {

                }
				if (ImGui::MenuItem("Project Settings"))
				{

				}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Game"))
            {
                if (ImGui::MenuItem("Run"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("ViewPort"))
					Editor::SetViewPort(true);

				if (ImGui::MenuItem("Scene Hierarchy"))
					Editor::SetSceneHierarchy(true);

				if (ImGui::MenuItem("Properties"))
					Editor::SetProperties(true);

				if (ImGui::MenuItem("Console"))
					Editor::SetConsole(true);

				if (ImGui::MenuItem("Content Browser"))
					Editor::SetContentBrowser(true);
                ImGui::EndMenu();
            }           
			ImGui::SameLine((ImGui::GetWindowContentRegionMax().x* 0.6f) - ( (ImGui::GetFontSize() + ImGui::GetStyle().ItemSpacing.x)));

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.2f, 0.7f, 0.0f));

			if (ImGui::Button(ICON_MDI_PLAY))
			{

			}
			if (ImGui::Button(ICON_MDI_PAUSE))
			{

			}
			if (ImGui::Button(ICON_MDI_STEP_FORWARD))
			{

			}
			float sizeOfGfxAPIDropDown = ImGui::GetFontSize() * 4;
			ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - ImGui::GetStyle().ItemSpacing.x * 2.0f - sizeOfGfxAPIDropDown);


			ImGui::Text("RHI: OpenGL");
			ImGui::PopStyleColor();
            ImGui::EndMenuBar();
        }
        ImGui::End();

    }
    void ImGuiLayer::OnEnd()
    {
        ImGui::Render();

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            //Application::GetInstance().GetContext().MakeCurrent(true);
        }
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

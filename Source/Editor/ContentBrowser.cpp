#include <Editor/ContentBrowser.h>
#include <Engine/System/FileSystem.h>
#include <Engine/IconsMaterialDesignIcons.h>

#include <ImGui/imgui.h>
namespace MeteorEngine
{

	Path pathAsset = Path("Assets/*");
	Path lastPathAsset;
	std::vector<Path> findPath;
	static bool isActive = true;
	void ContentBrowser::SetActive(bool active)
	{
		isActive = active;
	}
	ContentBrowser::ContentBrowser():
		m_currentPath(pathAsset.m_path)
	{
		FileSystem::Open(pathAsset);

		findPath = FileSystem::FindDirectory(pathAsset);
		findPath.erase(findPath.begin());

		m_DirectoryIcon = Texture2D::Create("Assets/Texture/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("Assets/Texture/FileIcon.png");
	}
	ContentBrowser::~ContentBrowser()
	{
		FileSystem::Close();

	}
	bool isNextDir = false;
	void ContentBrowser::OnUpdate()
	{
		if (isActive) {
			
			ImGui::Begin(ICON_MDI_FOLDER_STAR " Content Browser", &isActive);
			if (m_currentPath != pathAsset.m_path)
				if (ImGui::Button(ICON_MDI_BACKSPACE))
				{
					pathAsset = lastPathAsset;
					isNextDir = true;
				}

			if (isNextDir)
			{
				FileSystem::Open(pathAsset);
				findPath = FileSystem::FindDirectory(pathAsset);
				findPath.erase(findPath.begin());
				isNextDir = false;
			}
			static float thumbnailSize = 100;

			float panelWidth = ImGui::GetContentRegionAvail().x;
			int columnCount = (int)(panelWidth / thumbnailSize);
			if (columnCount < 1)
				columnCount = 1;

			ImGui::Columns(columnCount, 0, false);
			for (auto i : findPath)
			{
				if (i.isDirectory) {
					ImGui::PushID(i.fileName.c_str());
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)m_DirectoryIcon->GetTexture(), { thumbnailSize-20, thumbnailSize-20 });
					ImGui::PopStyleColor();
					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						lastPathAsset = pathAsset;
						pathAsset = Path("Assets/" + i.fileName + "/*");
						isNextDir = true;
					}
					ImGui::Text((" " + i.fileName).c_str());
					ImGui::NextColumn();
					ImGui::PopID();
				}
			}
			for (auto i : findPath)
			{
				if (!i.isDirectory) {
					ImGui::PushID(i.fileName.c_str());
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)m_FileIcon->GetTexture(), { thumbnailSize-20, thumbnailSize-20 });
					ImGui::PopStyleColor();
					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
					}
					ImGui::Text(i.fileName.c_str());
					ImGui::NextColumn();
					ImGui::PopID();
				}
			}
			ImGui::Columns(1);

			//ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
			ImGui::End();
		}
	}
}
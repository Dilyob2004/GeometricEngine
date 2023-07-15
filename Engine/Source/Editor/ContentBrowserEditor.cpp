#include "ContentBrowserEditor.h"
#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Generic/Path.h>
#include <Engine/Core/Misc/Log.h>
#include <ImGui/imgui.h>

String CurrentPath = SPath::GetEngineContentDir();
String PathContent = SPath::GetEngineContentDir();
String LastPathContent = SPath::GetEngineContentDir();
TArray<FPathInfo> ListOfPaths;
ContentBrowserEditor::ContentBrowserEditor()
{

	/*Image Directory;
	Directory.Load(SPath::GetEngineContentDir() + "/Textures/Editor/Folder_Base_512x.png");
	DirectoryTexture = new TextureResource2D(Directory);

	Image File;
	File.Load(SPath::GetEngineContentDir() + "/Textures/Editor/FileIcon.png");
	FileTexture = new TextureResource2D(File);
	*/


	Platform::GetFilesFromDirectory(PathContent, ListOfPaths);
}

ContentBrowserEditor::~ContentBrowserEditor()
{

}

void ContentBrowserEditor::OnTick()
{

}
bool IsNextDirection = false;
void ContentBrowserEditor::OnPaint()
{
	ImGui::Begin("ContetBrowser");

		/*if (PathContent != CurrentPath)
			if (ImGui::Button("Back"))
			{
				PathContent = LastPathContent;
				IsNextDirection = true;
			}


		if (IsNextDirection)
		{
			ListOfPaths.Clear();
			Platform::GetFilesFromDirectory(PathContent, ListOfPaths);
			IsNextDirection = false;
		}
		static float thumbnailSize = 100;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / thumbnailSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);
		for (auto Item : ListOfPaths)
		{
				ImGui::PushID(*Item.Name);
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				ImGui::ImageButton((Item.IsDirectory ? DirectoryTexture->GetHandle() : FileTexture->GetHandle()), {thumbnailSize, thumbnailSize});
				ImGui::PopStyleColor();
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && Item.IsDirectory)
				{
					LastPathContent = PathContent;
					PathContent  /= Item.Name;
					IsNextDirection = true;
				}
				ImGui::Text(*Item.Name);
				ImGui::NextColumn();
				ImGui::PopID();
		}
		ImGui::Columns(1);
	//ImGui::BeginChild("main", ImVec2(200, 200), true);
	//ImGui::EndChild();*/
	ImGui::End();
}
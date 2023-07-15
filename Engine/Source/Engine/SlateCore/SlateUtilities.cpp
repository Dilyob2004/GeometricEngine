#include "SlateUtilities.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

namespace SlateUtilities
{

	void DrawElem2Controls(const char* Label, Vector2f& values, float resetValue, float columnWidth)
	{
		auto boldFont = ImGui::GetIO().Fonts->Fonts[0];
		ImGui::PushID(Label);

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(Label);
			ImGui::NextColumn();

			ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
			ImGui::PushFont(boldFont);

			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;

			ImGui::PopFont();
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
			ImGui::PushFont(boldFont);
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValue;
			ImGui::PopFont();
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();


			ImGui::PopStyleVar();

			ImGui::Columns(1);
			ImGui::NewLine();

		ImGui::PopID();
	}
	void DrawElem1Controls(const char* label, float& values, float resetValue, float columnWidth)
	{
		auto boldFont = ImGui::GetIO().Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();


		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::NewLine();

		ImGui::PopID();
	}
}

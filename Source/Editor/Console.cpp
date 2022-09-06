#include <Editor/Console.h>
#include <ImGui/imgui.h>
#include <queue>
namespace MeteorEngine
{
	bool isActive = true;
	std::vector<std::pair<Vector4f, std::string> >  messages;
	Console::Console()
	{

	}
	Console::~Console()
	{

	}
	void Console::SetActive(bool active)
	{
		isActive = active;
	}
	void Console::OnUpdate()
	{
		if (isActive)
		{
			ImGui::Begin("Console", &isActive);
			ImGui::Text("Meteor Engine v1.0, GPU API: OpenGL v4.3");
			for(auto i: messages)
			{
				ImVec4 color = { messages.front().first.x,
								 messages.front().first.y,
								 messages.front().first.z,
								 messages.front().first.w };
				ImGui::TextColored(color, messages.front().second.c_str());
			}
			ImGui::End();
		}
	}
	void Console::SendMessage(const std::string& message)
	{
		messages.push_back({ {1, 1, 1, 1}, message });

	}
	void Console::SendError(const std::string& message)
	{
		messages.push_back({ {1, 0, 0, 1}, message });

	}
	void Console::Send(const std::string& message, const Vector4f& color)
	{
		messages.push_back({ color, message });
	}
}
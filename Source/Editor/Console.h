#ifndef CONSOLE_H
#define CONSOLE_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector4.h>
namespace MeteorEngine
{
	class METEOR_API Console
	{
	public:
		Console();
		~Console();
		void OnUpdate();
		static void SendMessage(const std::string&);
		static void SendError(const std::string&);
		static void Send(const std::string&, const Vector4f&);

		static void SetActive(bool);
	};
}
#endif // !CONSOLE_H

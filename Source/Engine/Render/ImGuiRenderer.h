#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H
#include <Engine/Core/Core.h>
#include <Engine/Math/Vector2.h>
namespace MeteorEngine
{
	class METEOR_API ImGuiRenderer
	{
	public:
		static ImGuiRenderer* Create(const Vector2u&, bool);
		virtual ~ImGuiRenderer() {}
		virtual void Render() = 0;
		virtual void OnResize(const Vector2u& size) = 0;
		virtual void Clear() = 0;
		virtual void BuildFontTexture() = 0;

	};
}
#endif // !IMGUIRENDERER_H

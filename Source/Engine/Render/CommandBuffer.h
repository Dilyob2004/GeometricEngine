#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
namespace MeteorEngine
{
	enum class CommandBufferState
	{
		ReadyForBegin,
		IsInsideBegin,
		IsInsideRenderPass,
		HasEnded,
		Submitted
	};
	class METEOR_API CommandBuffer
	{
	public:
		virtual ~CommandBuffer() {}
		virtual CommandBufferState	GetState() const = 0;
		static  CommandBuffer* Create();
		virtual bool Init(bool) = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Submit() = 0;
		virtual void UpdateViewport(const Vector2u&, bool) = 0;
		virtual bool Flush() = 0;
	};
}
#endif // !COMMANDBUFFER_H




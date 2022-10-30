#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#include <Engine/Core/Config.h>
namespace MeteorEngine
{

	class METEOR_API UniformBuffer
	{
	public:
		static UniformBuffer* Create(cp0*, u32);
		virtual ~UniformBuffer() {}
		virtual void SetData(cp0*, u32) = 0;
	};
}
#endif // !UNIFORMBUFFER_H

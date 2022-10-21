#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Render/Texture.h>
#include <vector>
namespace MeteorEngine
{
    struct FrameBufferSpec
    {
    };
    class METEOR_API FrameBuffer
    {
    public:
		static FrameBuffer* Create(const FrameBufferSpec&);
        virtual ~FrameBuffer() {}
        virtual void Resize(const Vector2u &) = 0;
        virtual u32 GetFrameBuffer() const  = 0;
        virtual const FrameBufferSpec& GetSpecification() const = 0;
    };
}
#endif // FRAMEBUFFER_H

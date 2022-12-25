#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{
    class METEOR_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        virtual void Bind(CommandBuffer*) const = 0;
        virtual void UnBind() const = 0;

		virtual void ReleasePointer() = 0;
		virtual void* GetPointer() = 0;
		virtual void SetData(f32*, u32) = 0;
		virtual void Resize(u32) = 0;
		virtual u32 GetSize() const = 0;
        static VertexBuffer *Create(f32 *vertices, u32 size);
    };
}
#endif // VERTEXBUFFER_H

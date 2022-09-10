#include <Engine/Render/OpenGL/OpenGLIndexBuffer.h>
#include <Engine/Render/IndexBuffer.h>
namespace MeteorEngine
{
    IndexBuffer *IndexBuffer::Create(u32 *indices, u32 size)
    {
        return new OpenGLIndexBuffer(indices, size);
    }
}

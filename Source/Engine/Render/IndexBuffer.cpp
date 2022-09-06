#include "IndexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
namespace MeteorEngine
{
    IndexBuffer *IndexBuffer::Create(u32 *indices, u32 size)
    {
        return new OpenGLIndexBuffer(indices, size);
    }
}

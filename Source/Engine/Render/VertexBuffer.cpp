#include "VertexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
namespace MeteorEngine
{
    VertexBuffer *VertexBuffer::Create(float *vertices, u32 size)
    {
        return new OpenGLVertexBuffer(vertices, size);
    }
}

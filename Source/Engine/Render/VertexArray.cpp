#include "VertexArray.h"
#include "OpenGL/OpenGLVertexArray.h"
namespace MeteorEngine
{
    VertexArray *VertexArray::Create()
    {
        return new OpenGLVertexArray();
    }
}

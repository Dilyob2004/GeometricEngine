#include <Engine/Render/VertexArray.h>
#include <Engine/Render/OpenGL/OpenGLVertexArray.h>
namespace MeteorEngine
{
    VertexArray *VertexArray::Create()
    {
        return new OpenGLVertexArray();
    }
}

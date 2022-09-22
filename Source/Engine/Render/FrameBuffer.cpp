#include <Engine/Render/OpenGL/OpenGLFrameBuffer.h>
#include <Engine/Render/FrameBuffer.h>
namespace MeteorEngine
{
    FrameBuffer* FrameBuffer::Create(const FrameBufferSpec& spec)
    {
        return new OpenGLFrameBuffer(spec);
    }

}

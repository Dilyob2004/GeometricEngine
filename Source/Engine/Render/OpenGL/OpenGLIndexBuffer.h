#ifndef OPENGLINDEXBUFFER_H
#define OPENGLINDEXBUFFER_H

#include "../../Core/Config.h"
#include "../IndexBuffer.h"
namespace MeteorEngine
{
    class METEOR_API OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(u32*, u32);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void UnBind() const;
        virtual u32 GetCount() const;

    private:
        u32 m_buffer;
        u32 m_count;
    };
}
#endif // OPENGLINDEXBUFFER_H

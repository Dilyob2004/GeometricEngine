#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include <Engine/Render/VertexArray.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer> >& GetVertexBuffer() const { return m_vertexBuffer; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }
    private:
        u32 m_vertexArray;
        std::vector<std::shared_ptr<VertexBuffer> > m_vertexBuffer;
        std::shared_ptr<IndexBuffer>                m_indexBuffer;
    };
}
#endif // OPENGLVERTEXARRAY_H

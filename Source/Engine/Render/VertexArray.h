#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <Engine/Core/Config.h>
#include <Engine/Render/VertexBuffer.h>
#include <Engine/Render/IndexBuffer.h>
#include <memory>
namespace MeteorEngine
{
    class METEOR_API VertexArray
    {
    public:
        virtual ~VertexArray() {}
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &)   = 0;
        virtual const std::vector<std::shared_ptr<VertexBuffer> >& GetVertexBuffer() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
        static VertexArray *Create();
    };
}
#endif // VERTEXARRAY_H

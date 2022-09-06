#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
    class METEOR_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind()     const   = 0;
        virtual void UnBind()   const   = 0;
        virtual u32 GetCount()  const   = 0;

        static IndexBuffer *Create(u32* , u32);
    };
}
#endif // INDEXBUFFER_H

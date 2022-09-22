#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H
#include <Engine/Render/FrameBuffer.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLFrameBuffer: public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpec& spec);
        virtual ~OpenGLFrameBuffer();
        virtual u32 GetFrameBuffer() const override{ return m_frameBuffer; }
        virtual const FrameBufferSpec& GetSpecification() const override { return m_specification; }
        virtual void Bind()     const override;
        virtual void UnBind()   const override;
        virtual void Resize(const Vector2u &) override;
    private:
		void AddTextureAttachment(Texture2D* );
        void Invalidate();


		std::vector<u32>		m_AttachmentData;
		FrameBufferSpec			m_specification{};
        u32 m_frameBuffer = 0;
    };
}
#endif // OPENGLFRAMEBUFFER_

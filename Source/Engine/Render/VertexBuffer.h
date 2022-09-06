#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include <Engine/Core/Config.h>
#include <vector>
namespace MeteorEngine
{

    ////////////////////////////////////////////////////////////////////////////////////////
    static u32 ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;

            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;


            case ShaderDataType::Mat:       return 4;
            case ShaderDataType::Mat2:      return 4 * 2 * 2;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;


            case ShaderDataType::Bool:      return 1;
            case ShaderDataType::None:      return 0;
            }
        return 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    struct BufferElement
    {
        BufferElement() :
			m_name(""),
			m_type(ShaderDataType::None),
			m_size(0),
			m_offset(0),
			m_normalized(false) 
		{}
        BufferElement(ShaderDataType type, const std::string &name, bool normalized = false):
            m_name(name),
            m_type(type),
            m_size(ShaderDataTypeSize(type)),
            m_offset(0),
            m_normalized(normalized)
        {
        }
        u32 GetComponentCount() const
        {
            switch(m_type)
            {
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;

                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;


                case ShaderDataType::Mat:       return 1;
                case ShaderDataType::Mat2:      return 4;
                case ShaderDataType::Mat3:      return 9;
                case ShaderDataType::Mat4:      return 16;


                case ShaderDataType::Bool:      return 1;
                case ShaderDataType::None:      return 0;
            }
            return 0;
        }
        std::string     m_name;
        ShaderDataType  m_type;
        u32             m_size;
        u32             m_offset;
        bool            m_normalized;
    };

    class BufferLayout
    {
    public:
        BufferLayout():
            m_bufferElements(),
            m_stride(0)
        {
        }
        BufferLayout(const std::initializer_list<BufferElement>& bufferElements):
            m_bufferElements(bufferElements),
            m_stride(0)
        {
            CalculateOffsetAndStride();
        }
        inline u32 GetStride() const { return m_stride;}
        std::vector<BufferElement>::iterator begin() { return m_bufferElements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_bufferElements.end(); }

        std::vector<BufferElement>::const_iterator begin() const { return m_bufferElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_bufferElements.end(); }

        inline const std::vector<BufferElement> &GetElements() const { return m_bufferElements; }
    private:

        void CalculateOffsetAndStride()
        {
            u32 offset = 0;
            m_stride = 0;
            for(auto& element: m_bufferElements)
            {
                element.m_offset = offset;
                offset += element.m_size;
                m_stride += element.m_size;
            }
        }
        std::vector<BufferElement> m_bufferElements;

        u32 m_stride;
    };
    ////////////////////////////////////////////////////////////////////////////////////////
    class METEOR_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void SetBufferLayout(const BufferLayout& layouts) = 0;
        virtual const BufferLayout& GetBufferLayout() const = 0;

        static VertexBuffer *Create(float *vertices, u32 size);
    };
}
#endif // VERTEXBUFFER_H

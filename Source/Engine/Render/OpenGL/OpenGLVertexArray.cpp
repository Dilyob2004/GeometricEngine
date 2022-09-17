#include <Engine/Render/OpenGL/OpenGLVertexArray.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>


namespace MeteorEngine
{
    static GLenum ShaderDataTypeSizeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:
			case ShaderDataType::Float2:    
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
				return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:      
				return GL_INT;


            case ShaderDataType::Mat:
            case ShaderDataType::Mat2:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:      
				return GL_FLOAT;


            case ShaderDataType::Bool:      return GL_BOOL;
            case ShaderDataType::None:      return 0;

        }
        return 0;
    }
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_vertexArray);
    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        if(m_vertexArray)
            glDeleteVertexArrays(1, &m_vertexArray);
    }
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        glBindVertexArray(m_vertexArray);
			vertexBuffer->Bind();
			u32 index = 0;
			const auto& layout = vertexBuffer->GetBufferLayout();
			for(const auto& element: layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GetComponentCount(),
									  ShaderDataTypeSizeToOpenGLBaseType(element.m_type) ,
									  element.m_normalized ? GL_TRUE : GL_FALSE,
									  layout.GetStride(),
									  (const p0)(const s32*)element.m_offset);

				index++;
			}
			m_vertexBuffer.push_back(vertexBuffer);
			vertexBuffer->UnBind();
        glBindVertexArray(0);
    }
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(m_vertexArray);
			indexBuffer->Bind();
			m_indexBuffer = indexBuffer;
		glBindVertexArray(0);
    }
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_vertexArray);
    }
    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }
}

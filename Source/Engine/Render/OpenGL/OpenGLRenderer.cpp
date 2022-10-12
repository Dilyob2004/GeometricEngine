#include <Engine/Render/Texture.h>
#include <Engine/Render/VertexBuffer.h>
#include <Engine/Render/OpenGL/OpenGLRenderer.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
#include <Engine/Math/MathUtils.h>
namespace MeteorEngine
{
    Camera2D                        m_camera2D;
	Camera							m_camera3D;

	std::shared_ptr<Shader>         m_shader;
    std::shared_ptr<Shader>         m_shaderTexture;
	std::shared_ptr<VertexArray>    m_Pipeline;


    void OpenGLRenderer::InitEngine()
    {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);

		m_Pipeline.reset(VertexArray::Create());
        f32 squareVertices[] = {

             -1.f,  -1.f,  0.0f, 0.0f, 0.0f,
			  1.f,  -1.f,  0.0f, 1.0f, 0.0f,
			  1.f,   1.f,  0.0f, 1.0f, 1.0f,
             -1.f,   1.f,  0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetBufferLayout({
                                  { ShaderDataType::Float3, "a_Position" },
                                  { ShaderDataType::Float2, "a_TexCoord" }
                                  });


		m_Pipeline->AddVertexBuffer(squareVB);

        u32 squareIndices [] = {0, 1, 2, 2, 3, 0};

        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));


		m_Pipeline->SetIndexBuffer(squareIB);
        //////////////////////////////////////////////////////////////////////////////
        m_shader.reset(Shader::Create("Assets/Shaders/Quad.glsl"));
        m_shaderTexture.reset(Shader::Create("Assets/Shaders/Texture.glsl"));
    }
    void OpenGLRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderer::SetClearColor(const Vector4f& v)
    {
        glClearColor(v.x, v.y, v.z, v.w);
    }

    void OpenGLRenderer::SetViewPort(s32 x, s32 y, u32 w, u32 h)
    {
        glViewport(x, y, w, h);
    }
    void OpenGLRenderer::SetupProjection2D(Camera2D camera)
    {
		m_camera2D = camera;
    }
	void OpenGLRenderer::SetupProjection3D(Camera camera)
	{
		m_camera3D = camera;
	}
	void OpenGLRenderer::DrawQuad(const Matrix4f& transform, const Vector4f& color)
	{
		m_shader->Bind();
		m_shader->SetUniformFloat4("u_Color", color);
		m_shader->SetUniformMat4("u_ViewProjection", m_camera3D.GetViewProjection());
		m_shader->SetUniformMat4("u_Transform", transform);

		DrawIndexed(m_Pipeline);
		m_shader->UnBind();


	}
	void OpenGLRenderer::DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color)
	{
		Quaternion rotator(rotation);
		Matrix4f rotationM = toMatrix4(rotator);
		m_shader->Bind();
		m_shader->SetUniformFloat4("u_Color", color);
		m_shader->SetUniformMat4("u_ViewProjection", m_camera2D.GetViewProjectionMatrix());
		m_shader->SetUniformMat4("u_Transform", Translate(Matrix4f::Identity, position) * rotationM * Scale(Matrix4f::Identity, scale));
		DrawIndexed(m_Pipeline);		
		m_shader->UnBind();
	}
    void OpenGLRenderer::DrawTextureQuad(const std::shared_ptr<Texture> &texture, const Vector3f &position, const Vector3f & rotation, const Vector2f& size)
    {
		Quaternion rotator(rotation);
		Matrix4f rotationM = toMatrix4(rotator);
        texture->Bind(0);
        m_shaderTexture->Bind();
        m_shaderTexture->SetUniformInt("u_Texture", 0);
        m_shaderTexture->SetUniformMat4("u_ViewProjection", m_camera2D.GetViewProjectionMatrix());
        m_shaderTexture->SetUniformMat4("u_Transform", Translate(Matrix4f::Identity, position)* rotationM * Scale(Matrix4f::Identity, {size.x, size.y, 0}));

		DrawIndexed(m_Pipeline);
		m_shaderTexture->UnBind();
		texture->UnBind(0);
    }
    void OpenGLRenderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL);
		vertexArray->UnBind();
    }
}

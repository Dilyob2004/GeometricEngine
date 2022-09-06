#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H
#include <Engine/Render/Shader.h>

#include <string>
namespace  MeteorEngine
{
    class METEOR_API OpenGLShader : public Shader
    {
    public:
        OpenGLShader();
        OpenGLShader(const std::string &, ShaderType);
        OpenGLShader(const std::string &);
        OpenGLShader(const std::string &, const std::string &);
        virtual ~OpenGLShader();
        virtual void SetUniformMat4(const std::string&, const Matrix4f&);
        virtual void SetUniformFloat(const std::string&, float);
        virtual void SetUniformFloat2(const std::string&, const Vector2f&);
        virtual void SetUniformFloat3(const std::string&, const Vector3f&);
        virtual void SetUniformFloat4(const std::string&, const Vector4f&);


        virtual void SetUniformInt(const std::string&, int);
        virtual void SetUniformInt2(const std::string&, const Vector2i&);
        virtual void SetUniformInt3(const std::string&, const Vector3i&);
        virtual void SetUniformInt4(const std::string&, const Vector4i&);
        virtual void Bind() const;
        virtual void UnBind() const;
    private:
        void Compile(const char*,  const char*);
        u32 m_shaderProgram;
    };
}
#endif // OPENGLSHADER_H

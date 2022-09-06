#ifndef SHADER_H
#define SHADER_H

#include <Engine/Math/Vector2.h>
#include <Engine/Math/Vector3.h>
#include <Engine/Math/Vector4.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Core/Config.h>
#include <string>
namespace MeteorEngine
{
    class METEOR_API Shader
    {
    public:
        virtual ~Shader() { }
        static Shader *Create(const std::string &, const std::string &);
        static Shader *Create(const std::string &);
        static Shader *CreateType(const std::string &, ShaderType);

        virtual void SetUniformInt(const std::string&, int) = 0;
        virtual void SetUniformInt2(const std::string&, const Vector2i&) = 0;
        virtual void SetUniformInt3(const std::string&, const Vector3i&) = 0;
        virtual void SetUniformInt4(const std::string&, const Vector4i&) = 0;

        virtual void SetUniformFloat(const std::string&, float) = 0;
        virtual void SetUniformFloat2(const std::string&, const Vector2f&) = 0;
        virtual void SetUniformFloat3(const std::string&, const Vector3f&) = 0;
        virtual void SetUniformFloat4(const std::string&, const Vector4f&) = 0;
        virtual void SetUniformMat4(const std::string&, const Matrix4f&) = 0;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}
#endif // SHADER_H

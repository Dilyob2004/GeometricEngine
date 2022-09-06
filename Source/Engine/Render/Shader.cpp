#include <Engine/Render/Shader.h>
#include <Engine/Render/OpenGL/OpenGLShader.h>
namespace MeteorEngine
{
    Shader *Shader::Create(const std::string &fragment, const std::string &vertex)
    {
        return new OpenGLShader(fragment, vertex);
    }
    Shader *Shader::CreateType(const std::string &shader, ShaderType type)
    {
        return new OpenGLShader(shader, type);
    }

    Shader *Shader::Create(const std::string &shader)
    {
        return new OpenGLShader(shader);
    }
}

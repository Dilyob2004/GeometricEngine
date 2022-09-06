#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
namespace MeteorEngine
{
    Texture2D * Texture2D::Create(const std::string& path)
    {
        return new OpenGLTexture2D(path);
    }
}

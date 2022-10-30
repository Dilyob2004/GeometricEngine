#include <Engine/Render/Shader.h>
#include <Engine/Render/Vulkan/VkShader.h>
namespace MeteorEngine
{
    Shader *Shader::Create(const std::string &fragment, const std::string &vertex)
    {
		return new VulkanShader(fragment, vertex);
    }
}

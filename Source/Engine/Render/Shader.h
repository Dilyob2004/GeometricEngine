#ifndef SHADER_H
#define SHADER_H

#include <Engine/Math/Vector2.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Render/Structs.h>
#include <string>
namespace MeteorEngine
{
	class Pipeline;
    class METEOR_API Shader
    {
    public:
        virtual ~Shader() { }
        static Shader *Create(const std::string &, const std::string &);
		///static Shader *Create(const std::string &);

		virtual DescriptorSetInfo GetDescriptorInfo(u32 index) = 0;
		virtual const std::vector<ShaderType> GetShaderTypes() const = 0;
		virtual bool IsCompiled() const = 0;
		virtual std::vector<PushConstant>& GetPushConstants() = 0;

		virtual void Bind() const {};
		virtual void UnBind() const {};
    };
}
#endif // SHADER_H

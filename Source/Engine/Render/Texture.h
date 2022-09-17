#ifndef TEXTURE_H
#define TEXTURE_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
#include <string>
namespace MeteorEngine
{
    class METEOR_API Texture
    {
    public:
        virtual ~Texture() {}
        virtual Vector2u     GetSize()   const = 0;
        virtual u32			GetTexture() const = 0;
        virtual void        Bind(u32 slot = 0) const = 0;
        virtual void        UnBind(u32 slot = 0)    const = 0;
    };
    class METEOR_API Texture2D: public Texture
    {
    public:
        static Texture2D * Create(const std::string& );
    };
	class METEOR_API Texture3D : public Texture
	{
	public:
		static Texture3D* Create(const std::string&) { return NULL; }
	};
}
#endif // TEXTURE_H

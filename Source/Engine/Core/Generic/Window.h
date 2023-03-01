#ifndef WINDOW_H
#define WINDOW_H

#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Core/Types/StringView.h>
namespace GeometricEngine
{
	struct WindowInfoDefinition
	{
		F32 PositionX;
		F32 PositionY; 
		F32 SizeWidth;
		F32 SizeHeight;
		bool HasWindowBorder;
		bool IsRegilarWindow;
		StringView Title;
	};
    class METEOR_API Window
    {
    public:
        virtual ~Window(){}
        static Window* Create(const WindowInfoDefinition&);
        virtual void Show() = 0;
        virtual void Hide() = 0;

        virtual void Close() = 0;

        virtual bool IsOpen() = 0;
		virtual bool IsClose() = 0;

        virtual void SetPosition(const Vector2i&) = 0;
        virtual void SetSize(const Vector2u&) = 0;
        virtual void SetTitle(const StringView&) = 0;

        virtual Vector2u GetSize() const = 0;
        virtual Vector2i GetPosition() const = 0;
        virtual void* GetHandle() const = 0;
    };
}

#endif // WINDOW_H

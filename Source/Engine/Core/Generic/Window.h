#ifndef WINDOW_H
#define WINDOW_H

#include <Engine/Math/Vector2.h>
#include <Engine/Core/Misc/StringView.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Containers/Queue.h>
namespace GeometricEngine
{
	struct WindowDefinition
	{
		WindowDefinition()
			: PositionX(0)
			, PositionY(0)
			, SizeWidth(0)
			, SizeHeight(0)
			, HasBorder(true)
			, IsRegularWindow(false)
			, Title("")
		{
		}
		F32 PositionX;
		F32 PositionY;
		F32 SizeWidth;
		F32 SizeHeight;
		bool HasBorder;
		bool IsRegularWindow;
		StringView Title;
	};
    class GEOMETRIC_API Window
    {
    public:
        static Window* Create(const WindowDefinition&);
		virtual ~Window() {}
        virtual void Show() = 0;
        virtual void Hide() = 0;

        virtual void Close() = 0;

        virtual bool IsOpen() = 0;

        virtual void SetPosition(const Vector2i&) = 0;
        virtual void SetSize(const Vector2u&) = 0;
        virtual void SetTitle(const StringView&) = 0;
		virtual void SetIcon(const TVector<U8>&, U32, U32) = 0;

		virtual U32 GetWidth() const = 0;
		virtual U32 GetHeight() const = 0;
		virtual Vector2u GetSize() const = 0;
        virtual Vector2i GetPosition() const = 0;
        virtual void* GetHandle() const = 0;
    };
}

#endif // WINDOW_H

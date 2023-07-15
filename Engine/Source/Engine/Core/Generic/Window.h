#ifndef WINDOW_H
#define WINDOW_H

#include <Engine/Math/Vector2.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Containers/Array.h>

struct WindowDefinition
{
	WindowDefinition()
		: SizeWidth(0)
		, SizeHeight(0)
		, Fullscreen(false)
		, Title("")
	{
	}
	F32 SizeWidth;
	F32 SizeHeight;
	bool Fullscreen;
	String Title;
};
class GEOMETRIC_API Window
{
public:
    static Window* Create(const WindowDefinition&);
	virtual ~Window() {}
    virtual void Show() = 0;
    virtual void Hide() = 0;
	virtual void Restore() = 0;
	virtual void Maximized() = 0;
	virtual void Minimized() = 0;

    virtual void Close() = 0;

    virtual bool IsOpen() = 0;

    virtual void SetPosition(const Vector2f&) = 0;
    virtual void SetSize(const Vector2f&) = 0;
    virtual void SetTitle(const String&) = 0;
	virtual void SetIcon(const TArray<U8>&, U32, U32) = 0;

	virtual bool IsMaximized() const = 0;
	virtual I32 GetWindowBorderSize() const = 0;
	virtual U32 GetWidth() const = 0;
	virtual U32 GetHeight() const = 0;
	virtual Vector2f GetSize() const = 0;
    virtual Vector2f GetPosition() const = 0;
    virtual void* GetHandle() const = 0;
};

#endif // WINDOW_H

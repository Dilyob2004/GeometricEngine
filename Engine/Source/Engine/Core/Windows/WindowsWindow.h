#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H
#include <Engine/Core/Generic/Window.h>
#include <Windows.h>
class GEOMETRIC_API WindowsWindow: public Window
{
public:
    WindowsWindow(const WindowDefinition&);
    virtual ~WindowsWindow();

    virtual void Show() override;
    virtual void Hide() override;
    virtual void Restore() override;
    virtual void Maximized() override;
    virtual void Minimized() override;

    virtual bool IsOpen() override;
    virtual void Close() override;
    virtual I32 GetWindowBorderSize() const override;

    virtual void SetPosition(const Vector2f&)override;
    virtual void SetSize(const Vector2f&)override;
    virtual void SetTitle(const String&)override;

    virtual void SetIcon(const TArray<U8>&, U32, U32) override;


    virtual bool IsMaximized() const override; 
    virtual Vector2f GetSize() const override;
	virtual U32 GetWidth() const override;
	virtual U32 GetHeight() const override;
    virtual Vector2f GetPosition() const override;
    virtual void* GetHandle() const override;
private:
    int RegionWidth;
    int RegionHeight;

    HWND HandleWindow;
    HICON HandleIcon;
    WindowDefinition Definition;
};
#endif // WINDOWSWINDOW_H

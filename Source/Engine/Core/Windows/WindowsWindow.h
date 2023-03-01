#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Core/Generic/Window.h>
namespace GeometricEngine
{
    class METEOR_API WindowsWindow: public Window
    {
        public:
            WindowsWindow(const WindowInfoDefinition&);
            virtual ~WindowsWindow();

            virtual void Show() override;
            virtual void Hide() override;
            virtual bool IsOpen()override;
            virtual bool IsClose()override;
            virtual void Close()override;

            virtual void SetPosition(const Vector2i&)override;
            virtual void SetSize(const Vector2u&)override;
            virtual void SetTitle(const StringView&)override;

            virtual Vector2u GetSize() const override;
            virtual Vector2i GetPosition() const override;
            virtual void* GetHandle() const override;

			static void WndProc(HWND, UINT, WPARAM, LPARAM);
	private:
            HWND HandleWindow;
    };
}

#endif // WINDOWSWINDOW_H

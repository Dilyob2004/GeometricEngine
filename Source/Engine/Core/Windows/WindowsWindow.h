#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H
#include <Engine/Core/Generic/Window.h>
namespace GeometricEngine
{
    class GEOMETRIC_API WindowsWindow: public Window
    {
        public:
            WindowsWindow(const WindowDefinition&);
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
			virtual U32 GetWidth() const override;
			virtual U32 GetHeight() const override;
            virtual Vector2i GetPosition() const override;
            virtual void* GetHandle() const override;

			static void WndProc(HWND, UINT, WPARAM, LPARAM);
	private:
            HWND HandleWindow;
    };
}

#endif // WINDOWSWINDOW_H

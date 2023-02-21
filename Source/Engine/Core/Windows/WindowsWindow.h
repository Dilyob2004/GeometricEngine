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
            WindowsWindow(const std::string&, const Vector2u&);
            virtual ~WindowsWindow();

            virtual void Show();
            virtual void Hide();
            virtual bool IsOpen();
            virtual void Quit();

            virtual void SetPosition(const Vector2i&);
            virtual void SetSize(const Vector2u&);
            virtual void SetTitle(const std::string&);

            virtual Vector2u GetSize() const;
            virtual Vector2i GetPosition() const;
            virtual void* GetWindowPtr() const;
        private:


	private:
            HWND m_hwnd;
    };
}

#endif // WINDOWSWINDOW_H

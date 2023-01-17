#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include <windows.h>
#include <string>
#include <queue>
#include <memory>

#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Core/Event.h>
#include <Engine/Core/MouseCodes.h>
#include <Engine/Core/KeyCodes.h>
#include <Engine/Core/Window.h>
namespace MeteorEngine
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

            virtual bool PeekEvents(Event&);

            virtual void SetPosition(const Vector2i&);
            virtual void SetSize(const Vector2u&);
            virtual void SetTitle(const std::string&);

            virtual Vector2u GetSize() const;
            virtual Vector2i GetPosition() const;
            virtual void* GetWindowPtr() const;
			void OnEvent(UINT, WPARAM, LPARAM);
        private:
            KeyCode VirtualKeyCodeToIS(WPARAM, LPARAM);
            HWND        m_hwnd = NULL;
			Vector2u    m_lastSize;
            std::queue<Event> m_events;
    };
}

#endif // WINDOWSWINDOW_H

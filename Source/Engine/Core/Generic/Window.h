#ifndef WINDOW_H
#define WINDOW_H

#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Core/Event.h>

#include <string>
#include <memory>
namespace GeometricEngine
{

    class METEOR_API Window
    {
    public:
        virtual ~Window(){}
        static Window* Create(const std::string&, const Vector2u&);
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Quit() = 0;
        virtual bool IsOpen() = 0;
        virtual void SetPosition(const Vector2i&) = 0;
        virtual void SetSize(const Vector2u&) = 0;
        virtual void SetTitle(const std::string&) = 0;
        virtual Vector2u GetSize() const = 0;
        virtual Vector2i GetPosition() const = 0;
        virtual void* GetWindowPtr() const = 0;
    };
}

#endif // WINDOW_H

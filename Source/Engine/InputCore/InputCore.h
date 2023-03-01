#ifndef INPUTCORE_H
#define INPUTCORE_H
#include <Engine/Core/EngineModule.h>
#include <Engine/InputDevice/KeyCodes.h>
#include <Engine/InputDevice/MouseCodes.h>
namespace GeometricEngine
{
    class GEOMETRIC_API Input
    {
    public:
		static bool GetKey(KeyCode Key);
		static bool GetKeyDown(KeyCode Key);
		static bool GetKeyUp(KeyCode Key);

		static bool GetMouseButton(MouseCode Key);
		static bool GetMouseButtonDown(MouseCode Key);
		static bool GetMouseButtonUp(MouseCode Key);
    };
}

#endif // INPUTCORE_H

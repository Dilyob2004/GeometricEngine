#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Engine/InputDevice/InputDevice.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Keyboard : public InputDevice
	{
		
	public:
		FORCEINLINE bool GetKey(KeyCode Key)
		{
			return KeyAction[static_cast<I32>(Key)];
		}
		FORCEINLINE bool GetKeyDown(KeyCode Key)
		{
			return (KeyAction[static_cast<I32>(Key)]
				&& !PrevKeyAction[static_cast<I32>(Key)]);
		}
		FORCEINLINE bool GetKeyUp(KeyCode Key)
		{
			return (!KeyAction[static_cast<I32>(Key)]
				&& PrevKeyAction[static_cast<I32>(Key)]);
		}

		void OnKeyDown(KeyCode Key);
		void OnKeyUp(KeyCode Key);
		virtual void Tick() override;
		virtual void Reset() override;
	protected:
		explicit Keyboard() : InputDevice("Keyboard")
		{
			memset(KeyAction, false, sizeof(KeyAction));
			memset(PrevKeyAction, false, sizeof(PrevKeyAction));
		}

		bool KeyAction[101];
		bool PrevKeyAction[101];

	};
}
#endif
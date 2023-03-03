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
			return NowData.KeyAction[static_cast<I32>(Key)];
		}
		FORCEINLINE bool GetKeyDown(KeyCode Key)
		{
			return (NowData.KeyAction[static_cast<I32>(Key)]
				&& !PrevData.KeyAction[static_cast<I32>(Key)]);
		}
		FORCEINLINE bool GetKeyUp(KeyCode Key)
		{
			return (!NowData.KeyAction[static_cast<I32>(Key)]
				&& PrevData.KeyAction[static_cast<I32>(Key)]);
		}

		void OnKey(EventType Type, KeyCode Key);
		virtual void Tick() override;
		virtual void Reset() override;
	protected:
		explicit Keyboard() : InputDevice("Keyboard")
		{
		}
		struct Data
		{
			Data()
			{
				for (int i = 0; i < 100; i++)
					KeyAction[i] = false;
			}
			bool KeyAction[100];
		};
		Data NowData, PrevData;

	};
}
#endif
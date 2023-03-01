#include <Engine/InputDevice/Keyboard.h>

namespace GeometricEngine
{

	void Keyboard::OnKeyDown(KeyCode Key)
	{
		Event KeyEvent;
		KeyEvent.KeyData.Key = Key;
		KeyEvent.Type = EventType::KeyDown;
		QueueEvents.Push(KeyEvent);
	}
	void Keyboard::OnKeyUp(KeyCode Key)
	{
		Event KeyEvent;
		KeyEvent.KeyData.Key = Key;
		KeyEvent.Type = EventType::KeyUp;
		QueueEvents.Push(KeyEvent);
	}

	void Keyboard::Tick()
	{
		if (!QueueEvents.IsEmpty())
		{
			Event LastEvent = QueueEvents.Front();

			if (LastEvent.Type == EventType::KeyDown)
			{
				PrevKeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = KeyAction[static_cast<I32>(LastEvent.KeyData.Key)];
				KeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = true;
			}
			else
			{

				PrevKeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = KeyAction[static_cast<I32>(LastEvent.KeyData.Key)];
				KeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = false;
			}
			QueueEvents.Pop();

		}
	}
	void Keyboard::Reset()
	{
		memset(KeyAction, false, sizeof(KeyAction));
		memset(PrevKeyAction, false, sizeof(PrevKeyAction));
	}
}
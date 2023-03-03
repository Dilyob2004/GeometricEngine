#include <Engine/InputDevice/Keyboard.h>

namespace GeometricEngine
{

	void Keyboard::OnKey(EventType Type, KeyCode Key)
	{
		Event KeyEvent;
		KeyEvent.KeyData.Key = Key;
		KeyEvent.Type = Type;
		QueueEvents.Push(KeyEvent);
	}
	void Keyboard::Tick()
	{
		SMemory::Copy(&PrevData, &NowData, sizeof(Data));
		if (!QueueEvents.IsEmpty())
		{
			Event LastEvent = QueueEvents.Front();
			switch (LastEvent.Type)
			{
				case EventType::KeyDown:
					NowData.KeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = true;
				break;				
				case EventType::KeyUp:
					NowData.KeyAction[static_cast<I32>(LastEvent.KeyData.Key)] = false;
				break;
			}
			QueueEvents.Pop();

		}
	}
	void Keyboard::Reset()
	{
	}
}
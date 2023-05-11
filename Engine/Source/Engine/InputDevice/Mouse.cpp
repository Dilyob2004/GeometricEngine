#include <Engine/InputDevice/Mouse.h>
namespace GeometricEngine
{

	void Mouse::OnMouse(EventType Type, MouseCode Code)
	{
		Event MouseEvent;
		MouseEvent.Type = Type;
		MouseEvent.MouseData.Code = Code;
		QueueEvents.Push(MouseEvent);

	}
	void Mouse::OnMouseMove(const Vector2f& MovePosition)
	{
		Event MouseEvent;
		MouseEvent.Type = EventType::MouseMove;
		MouseEvent.MouseData.Position = MovePosition;
		QueueEvents.Push(MouseEvent);
	}
	void Mouse::OnMouseWheel(float Delta)
	{
		Event MouseEvent;
		MouseEvent.Type = EventType::MouseWheel;
		MouseEvent.MouseData.Delta = Delta;
		QueueEvents.Push(MouseEvent);
	}

	void Mouse::Tick()
	{
		SMemory::Copy(&PrevData, &NowData, sizeof(Data)); 
		NowData.Delta = 0;
		if (!QueueEvents.IsEmpty())
		{
			Event LastEvent = QueueEvents.Front();
			switch (LastEvent.Type)
			{
				case EventType::MouseDown:	
				case EventType::MouseDoubleClick:
					NowData.MouseCode[static_cast<int>(LastEvent.MouseData.Code)] = true;
					break;

				case EventType::MouseUp:
					NowData.MouseCode[static_cast<int>(LastEvent.MouseData.Code)] = false;
					break;

				case EventType::MouseMove:
					NowData.Position = LastEvent.MouseData.Position;
					break;

				case EventType::MouseWheel:
					NowData.Delta += LastEvent.MouseData.Delta;
					break;
			}
			QueueEvents.Pop();

		}
	}
	void Mouse::Reset()
	{

	}
}
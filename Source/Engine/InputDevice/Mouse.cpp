#include <Engine/InputDevice/Mouse.h>


namespace GeometricEngine
{

	void Mouse::OnMouseDown(MouseCode Code)
	{
		Event MouseEvent;
		MouseEvent.Type = EventType::MouseDown;
		MouseEvent.MouseData.Code = Code;
		QueueEvents.Push(MouseEvent);

	}
	void Mouse::OnMouseUp(MouseCode Code)
	{
		Event MouseEvent;
		MouseEvent.MouseData.Code = Code;
		MouseEvent.Type = EventType::MouseUp;
		QueueEvents.Push(MouseEvent);
	}
	void Mouse::OnMouseMove(const Vector2f& MovePosition)
	{
		Event MouseEvent;
		MouseEvent.MouseData.Position = MovePosition;
		QueueEvents.Push(MouseEvent);
	}
	void Mouse::OnMouseWheel(float Delta)
	{
		Event MouseEvent;
		MouseEvent.MouseData.Delta = Delta;
		QueueEvents.Push(MouseEvent);
	}

	void Mouse::Tick()
	{
		if (!QueueEvents.IsEmpty())
		{
			SMemory::Copy(&PrevData, &NowData, sizeof(Data));
			Event LastEvent = QueueEvents.Front();
			switch (LastEvent.Type)
			{
			case EventType::MouseDown:
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
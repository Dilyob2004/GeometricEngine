#include <Engine/InputDevice/EventWindow.h>

namespace GeometricEngine
{

	void EventWindow::OnResizeEvent(U32 Width, U32 Height)
	{
		Event KeyEvent;
		KeyEvent.Type = EventType::ResizedWindow;
		KeyEvent.ResizeData.Width = Width;
		KeyEvent.ResizeData.Height = Height;
		QueueEvents.Push(KeyEvent);

	}
	void EventWindow::OnClosedEvent()
	{
		Event KeyEvent;
		KeyEvent.Type = EventType::ClosedWindow;
		QueueEvents.Push(KeyEvent);
	}
	void EventWindow::Tick()
	{
		NowData.Resized = false;
		if (!QueueEvents.IsEmpty())
		{
			Event LastEvent = QueueEvents.Front();
			switch (LastEvent.Type)
			{
				case EventType::ResizedWindow:
					NowData.Resized = true;
					NowData.Width = LastEvent.ResizeData.Width;
					NowData.Height = LastEvent.ResizeData.Height;
					break;
				case EventType::ClosedWindow:
					NowData.Closed = true;
					break;
			}
			QueueEvents.Pop();

		}
	}
	void EventWindow::Reset()
	{

	}
}
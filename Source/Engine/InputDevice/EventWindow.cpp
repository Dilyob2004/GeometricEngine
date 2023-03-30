#include <Engine/InputDevice/EventWindow.h>

namespace GeometricEngine
{

	void EventWindow::OnResizeEvent(U32 Width, U32 Height, bool LastResized)
	{
		Event KeyEvent;
		KeyEvent.Type = EventType::ResizedWindow;
		KeyEvent.ResizeData.Width = Width;
		KeyEvent.ResizeData.Height = Height;
		KeyEvent.ResizeData.Resized = LastResized;
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
		if (!QueueEvents.IsEmpty())
		{
			Event LastEvent = QueueEvents.Front();
			switch (LastEvent.Type)
			{
				case EventType::ResizedWindow:
					NowData.Resized = LastEvent.ResizeData.Resized;
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
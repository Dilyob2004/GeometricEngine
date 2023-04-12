#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H
#include <Engine/InputDevice/InputDevice.h>

namespace GeometricEngine
{

	class GEOMETRIC_API EventWindow : public InputDevice
	{
	public:

		FORCEINLINE bool OnResized(U32& OutWidth, U32& OutHeight)
		{
			OutWidth = NowData.Width;
			OutHeight = NowData.Height;
			return NowData.Resized;
		}
		FORCEINLINE bool OnResized()
		{
			return NowData.Resized;
		}
		FORCEINLINE bool OnClosed() 
		{ 
			return NowData.Closed; 
		}
		void OnResizeEvent(U32, U32);
		void OnClosedEvent();
		virtual void Tick() override;
		virtual void Reset() override;
		explicit EventWindow() : InputDevice("EventWindow")
		{
		}
	protected:
		struct Data
		{
			Data() : Resized(false), Closed(false), Width(0), Height(0) {}

			U32 Width, Height;
			bool Resized;
			bool Closed;
		};
		Data NowData;
	};
}
#endif // !EVENTWINDOW_H

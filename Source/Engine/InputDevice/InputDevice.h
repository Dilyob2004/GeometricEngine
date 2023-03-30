#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H
#include <Engine/InputDevice/KeyCodes.h>
#include <Engine/InputDevice/MouseCodes.h>
#include <Engine/Core/Containers/Queue.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Math/Vector2.h>
namespace GeometricEngine
{
	class GEOMETRIC_API InputDevice
	{
	public:
		enum class EventType
		{
			None,
			KeyDown,
			KeyUp,
			MouseDown,
			MouseUp,
			MouseWheel,
			MouseMove,
			MouseDoubleClick,
			Char,
			ClosedWindow,
			ResizedWindow
		};
		class Event
		{
		public:
			EventType Type;
			Event()
				: Type(EventType::None)
				, CharData()
			{

			}
			union
			{
				struct
				{
					U32 Width;
					U32 Height;
					bool Resized;
				}ResizeData;

				struct
				{
					CHAR Char;
				} CharData;

				struct
				{
					KeyCode Key;
				}KeyData;


				struct
				{
					MouseCode Code;
					Vector2f Position;
					F32 Delta;
				}MouseData;

			};
		};
		FORCEINLINE const String& GetDeviceName() const
		{
			return NameDevice;
		}
	protected:
		explicit InputDevice(const String& Name)
			: NameDevice(Name)
			, QueueEvents()
		{
		}
		String NameDevice;
		TQueue<Event> QueueEvents;
	public:
		virtual void Reset()
		{
			QueueEvents.Clear();
		}
		virtual void Tick() = 0;
	};
}
#endif // !INPUTDEVICE_H

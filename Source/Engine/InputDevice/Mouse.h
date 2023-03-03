#ifndef MOUSE_H
#define MOUSE_H

#include <Engine/InputDevice/InputDevice.h>
namespace GeometricEngine
{ 
	class GEOMETRIC_API Mouse : public InputDevice
	{
	public:

		FORCEINLINE bool GetButtonDown(MouseCode Code) const
		{

			return (NowData.MouseCode[static_cast<int>(Code)]
				&& !PrevData.MouseCode[static_cast<int>(Code)]);
		}
		FORCEINLINE bool GetButton(MouseCode Code) const
		{
			return NowData.MouseCode[static_cast<int>(Code)];
		}
		FORCEINLINE bool GetButtonUp(MouseCode Code) const
		{
			return !NowData.MouseCode[static_cast<int>(Code)]
				&& PrevData.MouseCode[static_cast<int>(Code)];
		}
		FORCEINLINE Vector2f GetPosition() const
		{
			return NowData.Position;
		}
		FORCEINLINE Vector2f GetPositionDelta() const
		{
			return NowData.Position - PrevData.Position;
		}
		FORCEINLINE F32 GetWhellDelta() const
		{
			return NowData.Delta;
		}
		void OnMouse(EventType Type, MouseCode);
		void OnMouseMove(const Vector2f& );
		void OnMouseWheel(float);

		virtual void Tick() override;
		virtual void Reset() override;
	protected:
		explicit Mouse() : InputDevice("Mouse")
		{
		}
		struct Data
		{
			Data()
			{
				Delta = 0;
				Position = Vector2f(0, 0);

				for (int i = 0; i < 10; i++)
					MouseCode[i] = false;

			}
			F32			Delta;
			Vector2f	Position;
			bool		MouseCode[10];
		};

		Data PrevData, NowData;
	};
}
#endif // !MOUSE_H

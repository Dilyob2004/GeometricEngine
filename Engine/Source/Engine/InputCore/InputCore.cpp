
#include <Engine/InputCore/InputCore.h>
#include <Engine/Core/Windows/WindowsInput.h>
namespace GeometricEngine
{
	bool Input::GetKey(KeyCode Key)
	{
		return WindowsInput::GetKey(Key);
	}
	bool Input::GetKeyDown(KeyCode Key)
	{
		return WindowsInput::GetKeyDown(Key);
	}
	bool Input::GetKeyUp(KeyCode Key)
	{
		return WindowsInput::GetKeyUp(Key);
	}	
	bool Input::GetMouseButton(MouseCode Code)
	{
		return WindowsInput::GetMouseButton(Code);
	}
	bool Input::GetMouseButtonDown(MouseCode Code)
	{
		return WindowsInput::GetMouseButtonDown(Code);
	}
	bool Input::GetMouseButtonUp(MouseCode Code)
	{
		return WindowsInput::GetMouseButtonUp(Code);
	}
	Vector2f Input::GetMousePosition()
	{
		return WindowsInput::GetMousePosition();
	}
	Vector2f Input::GetMousePositionDelta()
	{
		return WindowsInput::GetMousePositionDelta();
	}
	F32		Input::GetMouseWhellDelta()
	{
		return WindowsInput::GetMouseWhellDelta();
	}
	bool Input::OnWindowClosed()
	{
		return WindowsInput::OnClosed();
	}
	bool Input::OnWindowResized(U32& OutWidth, U32& OutHeight)
	{
		return WindowsInput::OnResized(OutWidth, OutHeight);
	}
	bool Input::OnWindowResized()
	{
		return WindowsInput::OnResized();
	}
}


#include <Engine/InputCore/InputCore.h>
#include <Engine/Core/Windows/WindowsInput.h>
#include <Engine/InputCore/InputModule.h>
namespace GeometricEngine
{
	InputModule::InputModule() : EngineModule("InputModule") 
	{
	}
	InputModule::~InputModule()
	{
	}
	void InputModule::Tick()
	{
		WindowsInput::Tick();
	}	
	void InputModule::LateTick()
	{
	}
	void InputModule::DeInitialize()
	{
		WindowsInput::DeInitialize();
	}
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
	bool InputModule::Initialize()
	{
		return WindowsInput::Initialize();
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
}

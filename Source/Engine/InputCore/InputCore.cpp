#include <Engine/InputCore/InputCore.h>
#include <Engine/Core/Windows/WindowsInput.h>
namespace GeometricEngine
{
	class InputModule : public EngineModule
	{
	public:
		InputModule();
		virtual ~InputModule();
		bool Initialize() override;
		void Tick() override;
		void LateTick() override;
		void DeInitialize() override;
	};
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
	InputModule GInputModuleInstance;
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
}

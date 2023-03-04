#ifndef INPUTMODULE_H
#define INPUTMODULE_H
#include <Engine/Core/EngineModule.h>
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
}

#endif // !INPUTMODULE_H

#ifndef RHIMODULE_H
#define RHIMODULE_H
#include <Engine/Core/EngineModule.h>
namespace GeometricEngine
{
	class RHIModule : public EngineModule
	{
	public:
		RHIModule();
		virtual ~RHIModule();
		bool Initialize() override;
		void DeInitialize() override;
	};
}
#endif // !RHIMODULE_H

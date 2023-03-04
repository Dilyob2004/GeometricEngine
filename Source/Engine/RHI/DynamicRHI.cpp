#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/RHIModule.h>
#include <Engine/Core/Application.h>
namespace GeometricEngine
{
	DynamicRHI* GDynamicRHI = NULL;
	RHIModule::RHIModule() : EngineModule("RHIModule")
	{

	}
	RHIModule::~RHIModule()
	{
	}
	bool RHIModule::Initialize()
	{
		GDynamicRHI = DynamicRHI::CreateDynamicRHI();
		if (!GDynamicRHI || !GDynamicRHI->Initialize())
			return false;
		return true;
	}
	void RHIModule::DeInitialize()
	{
	}
}
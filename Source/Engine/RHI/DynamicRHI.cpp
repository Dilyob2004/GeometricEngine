#include <Engine/RHI/DynamicRHI.h>
namespace GeometricEngine
{
	DynamicRHI* GDynamicRHI = NULL;
	bool InitializeDynamicRHI()
	{
		GDynamicRHI = DynamicRHI::CreateDynamicRHI();
		if (!GDynamicRHI->Initialize()) 
			return false;
		return true;
	}
}
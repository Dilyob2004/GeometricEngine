#include <Engine/RHI/DynamicRHI.h>

DynamicRHI* GDynamicRHI = NULL;
bool InitializeDynamicRHI()
{
	GDynamicRHI = DynamicRHI::CreateDynamicRHI();
	if (!GDynamicRHI->Initialize()) 
		return false;
	return true;
}

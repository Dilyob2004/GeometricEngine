#include <Engine/RHI/DynamicRHI.h>


namespace GeometricEngine
{
	class VertexBuffer
	{
	public:



		void Tick()
		{
			GDynamicRHI->RHIBindVertexBuffer(GVertexBuffers);
		}


	private:
		RHIVertexBuffer* GVertexBuffers;
	};
}
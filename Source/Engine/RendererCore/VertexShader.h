#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include <Engine/RHI/DynamicRHI.h>
namespace GeometricEngine
{
	class VertexShader
	{
		struct VertexData
		{
			RHIVertexShader* VertexShader;
			RHIVertexLayout* VertexLayout;
		};
	public:

		void AddRenderer(const TVector<U32>& Code, const TVector<BufferElement>& VertexLayoutElements)
		{
			VertexData Data;
			Data.VertexShader = GDynamicRHI->RHICreateVertexShader(Code);
			Data.VertexLayout = GDynamicRHI->RHICreateVertexLayout(Data.VertexShader, VertexLayoutElements);
			VertexDataCache.Push(Data);
		}
		VertexData GetVertexDataByIndex(I32 Index) const
		{
			return VertexDataCache[Index];
		}
		void Tick()
		{
			for (VertexData Data : VertexDataCache) 
			{
				GDynamicRHI->RHIBindVertexLayout(Data.VertexLayout);
				GDynamicRHI->RHIBindVertexShader(Data.VertexShader);
			}
		}

	private:

		TVector<VertexData>  VertexDataCache;
	};
}
#endif // !VERTEXSHADER_H

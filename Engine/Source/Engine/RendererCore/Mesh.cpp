#include "Mesh.h"

#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>

struct
{
	FMatrix4 ViewProjection { 1.0f };
	FMatrix4 View { 1.0f };
}CBufferMesh;

Mesh::Mesh()
	: VertexBuffer(NULL)
	, IndexBuffer(NULL)
	, UniformBuffer(NULL)
{

}
Mesh::Mesh(const TArray <VertexData>& VerticesData, const TArray<U32>& IndicesData)
	: Indices(IndicesData)
{
	VertexBuffer = GDynamicRHI->RHICreateVertexBuffer(VerticesData.Pointer(), VerticesData.Count() * sizeof(VertexData), sizeof(VertexData));
	IndexBuffer = (GDynamicRHI->RHICreateIndexBuffer(IndicesData.Pointer(), 4 * IndicesData.Count()));

	UniformBuffer = (GDynamicRHI->RHICreateUniformBuffer(&CBufferMesh, sizeof(CBufferMesh)));
	SamplerState = GDynamicRHI->RHICreateSamplerState(RHISamplerStateDefinition());


}
Mesh::~Mesh()
{

}

void Mesh::OnTick(RHITexture2D* RenderTarget, const Camera& CameraScene)
{
	{
		CBufferMesh.ViewProjection = CameraScene.GetViewProjection();
		CBufferMesh.View = CameraScene.GetViewProjection();
		//GDynamicRHI->RHIUpdateUniformBuffer(UniformBuffer, &CBufferMesh, sizeof(CBufferMesh));
	}
	GDynamicRHI->RHIDrawPrimitiveIndexed(VertexBuffer, IndexBuffer, Indices.Count(), 0);
}





Mesh* MakeQuad()
{
	/*TArray<VertexData> VerticesData;
	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0, 0)));
	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.0f), Vector3f(1.0f, 1.0f, 0.0f), Vector2f(0, 0)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0, 0)));
	*/
	return NULL;// new Mesh(VerticesData, { 0, 2, 1, 0, 3, 2 });
}	
Mesh* MakeCube()
{
	TArray<VertexData> VerticesData;

	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0, 0)));

	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0, 0)));

	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0, 0)));

	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0, 0)));

	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0, 0)));

	VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1, 1)));
	VerticesData.Push(VertexData(Vector3f( 0.5f, -0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0, 1)));
	VerticesData.Push(VertexData(Vector3f( 0.5f,  0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1, 0)));
	VerticesData.Push(VertexData(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0, 0)));

	return new Mesh(VerticesData,
								{
									3,1,0,
									2,1,3,

									6,4,5,
									7,4,6,

									11,9,8,
									10,9,11,

									14,12,13,
									15,12,14,

									19,17,16,
									18,17,19,

									22,20,21,
									23,20,22 });
}


/*

Index indices[] =
{
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

*/
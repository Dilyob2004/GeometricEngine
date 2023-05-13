#include "Mesh.h"

namespace GeometricEngine
{
	struct
	{
		Matrix4f ViewProjection { 1.0f };
	}CBufferMesh;

	Mesh::Mesh()
		: VertexBuffer(NULL)
		, IndexBuffer(NULL)
		, UniformBuffer(NULL)
	{

	}
	Mesh::Mesh(const TVector <Vertex2DData>& VerticesData, const TVector<U32>& IndicesData)
		: Indices(IndicesData)
	{
		VertexBuffer = GDynamicRHI->RHICreateVertexBuffer(VerticesData.Pointer(), VerticesData.GetCount() * sizeof(Vertex2DData), sizeof(Vertex2DData));
		IndexBuffer		= (GDynamicRHI->RHICreateIndexBuffer(IndicesData.Pointer(), 4 * IndicesData.GetCount()));
		UniformBuffer	= (GDynamicRHI->RHICreateUniformBuffer(&CBufferMesh, sizeof(CBufferMesh)));
	}
	Mesh::Mesh(const TVector <VertexData>& VerticesData, const TVector<U32>& IndicesData)
		: Indices(IndicesData)
	{
		VertexBuffer = GDynamicRHI->RHICreateVertexBuffer(VerticesData.Pointer(), VerticesData.GetCount() * sizeof(VertexData), sizeof(VertexData));
		IndexBuffer = (GDynamicRHI->RHICreateIndexBuffer(IndicesData.Pointer(), 4 * IndicesData.GetCount()));
		UniformBuffer = (GDynamicRHI->RHICreateUniformBuffer(&CBufferMesh, sizeof(CBufferMesh)));
	}
	Mesh::~Mesh()
	{

	}

	void Mesh::OnTick(RHIVertexShader* Shader, const Matrix4f& ViewProjection)
	{

		if (CBufferMesh.ViewProjection != ViewProjection)
		{
			CBufferMesh.ViewProjection = ViewProjection;
			GDynamicRHI->RHIUpdateUniformBuffer(UniformBuffer, &CBufferMesh, sizeof(CBufferMesh));
		}

		GDynamicRHI->RHISetUniformBuffer(Shader, UniformBuffer);

		GDynamicRHI->RHIDrawPrimitiveIndexed(VertexBuffer, IndexBuffer, Indices.GetCount(), 0);
	}





	Mesh* MakeQuad()
	{
		TVector<VertexData> VerticesData;
		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.0f), Vector3f(1.0f, 1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f)));
		return new Mesh(VerticesData, { 0, 2, 1, 0, 3, 2 });
	}	
	Mesh* MakeCube()
	{
		TVector<VertexData> VerticesData;

		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f)));

		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f)));

		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f)));

		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f)));

		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));
		VerticesData.Push(VertexData(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, -1.0f)));

		VerticesData.Push(VertexData(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f)));
		VerticesData.Push(VertexData(Vector3f( 0.5f, -0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f)));
		VerticesData.Push(VertexData(Vector3f( 0.5f,  0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f)));
		VerticesData.Push(VertexData(Vector3f(-0.5f,  0.5f,  0.5f), Vector3f(0.0f, 0.0f, 1.0f)));

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
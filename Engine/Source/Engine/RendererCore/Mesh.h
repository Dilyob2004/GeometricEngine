#ifndef MESH_H
#define MESH_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Vector2.h>
#include "ShaderResource.h"
namespace GeometricEngine
{
	struct Vertex2DData
	{
		Vertex2DData()
			: Position(0, 0, 0)
			, UV(0, 0)
		{
		}
		Vertex2DData(Vector3f InPosition, Vector2f InUV)
			: Position(InPosition)
			, UV(InUV)
		{
		}
		Vector3f Position;
		Vector2f UV;
	};
	struct VertexData
	{
		VertexData()
			: Position(0, 0, 0)
			, Normal(0, 0, 0)
		{
		}
		VertexData(Vector3f InPosition, Vector3f InNormal)
			: Position(InPosition)
			, Normal(InNormal)
		{
		}
		Vector3f Position;
		Vector3f Normal;
	};
	class GEOMETRIC_API Mesh
	{
	public:
		Mesh();
		Mesh(const TVector < Vertex2DData>&, const TVector<U32>&);
		Mesh(const TVector < VertexData>&, const TVector<U32>&);
		~Mesh();
		void OnTick(RHIVertexShader*, const Matrix4f&	);
		RHIVertexBuffer* GetVertexBuffer()const { return VertexBuffer; }
		RHIIndexBuffer* GetIndexBuffer()const { return IndexBuffer; }
		RHIUniformBuffer* GetUniformBuffer() const { return UniformBuffer; }
	private:
		RHIVertexBuffer*	VertexBuffer;
		RHIIndexBuffer*		IndexBuffer;
		RHIUniformBuffer*  UniformBuffer;
		TVector<U32> Indices;
	};

	extern GEOMETRIC_API Mesh* MakeQuad();
	extern GEOMETRIC_API Mesh* MakeCube();
}
#endif // !MESH_H

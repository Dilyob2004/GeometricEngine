#ifndef MESH_H
#define MESH_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Renderer/Camera.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Vector2.h>


struct VertexData
{
	VertexData()
		: Position(0, 0, 0)
		, Normal(0, 0, 0)
		, TexCoord(0, 0)
	{
	}
	VertexData(Vector3f InPosition, Vector3f InNormal, Vector2f InTexCoord)
		: Position(InPosition)
		, Normal(InNormal)
		, TexCoord(InTexCoord)
	{
	}
	Vector3f Position;
	Vector3f Normal;
	Vector2f TexCoord;
};
class Mesh
{
public:
	Mesh();
	Mesh(const TArray < VertexData>&, const TArray<U32>&);
	~Mesh();
	void OnTick(RHITexture2D*, const Camera& );
	RHIVertexBuffer* GetVertexBuffer()const { return VertexBuffer; }
	RHIIndexBuffer* GetIndexBuffer()const { return IndexBuffer; }
	RHIUniformBuffer* GetUniformBuffer() const { return UniformBuffer; }
private:
	RHIVertexBuffer*	VertexBuffer;
	RHIIndexBuffer*		IndexBuffer;
	RHIUniformBuffer*  UniformBuffer;
	RHISamplerState* SamplerState;
	TArray<U32> Indices;
};

extern GEOMETRIC_API Mesh* MakeQuad();
extern GEOMETRIC_API Mesh* MakeCube();

#endif // !MESH_H

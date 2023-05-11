cbuffer VSConstants
{
	matrix WorldViewProjection;
};
struct VertexOut 
{
    float4 Position : SV_POSITION;
	float2 UV: UV;
};

VertexOut VSMain( in float3 InPosition : POSITION,
				  in float2 InUV    : UV) 
{
	VertexOut Out 	= (VertexOut) 0;
	Out.Position	=  mul(WorldViewProjection, float4(InPosition, 1.0));
	Out.UV 			=  InUV;
	return Out;
}

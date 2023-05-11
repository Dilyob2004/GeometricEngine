cbuffer VSConstants
{
	matrix WorldViewProjection;
};

struct VertexOut 
{
    float4 Position : SV_POSITION;
	float3 Normal: TEXCOORD0;
};
VertexOut VSMain( in float3 Position : POSITION,
				  in float3 Normal: NORMAL) 
{
	VertexOut Out 	= (VertexOut)0;
	Out.Position	= mul(WorldViewProjection, float4(Position, 1.0));
	Out.Normal 		= Normal;
	return Out;
}
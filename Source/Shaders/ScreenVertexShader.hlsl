cbuffer VSConstants
{
	matrix WorldViewProjection;
};

struct VertexOut 
{
    float4 Position : SV_POSITION;
	float4 Color: COLOR;
	float2 TextureCoordinates: UV;
};
VertexOut VSMain( in float3 InPosition : POSITION,
				  in float3 InColor    : COLOR,
				  in float2 TextureCoordinates: UV) 
{
	VertexOut Out 	= (VertexOut) 0;
	Out.Position	= mul(WorldViewProjection, float4(InPosition, 1.0));
	Out.Color 		= float4(InColor, 1.0);
	Out.TextureCoordinates = TextureCoordinates;
	return Out;
}
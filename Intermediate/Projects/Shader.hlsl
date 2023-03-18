/**cbuffer VSConstants
{
	matrix WorldViewProjection;
};*/

struct VertexOut 
{
    float4 Position : SV_POSITION;
	float4 Color: COLOR0;
};

VertexOut VSMain( in float3 InPosition : POSITION,
				  in float3 InColor    : COLOR) 
{
	VertexOut Out 	= (VertexOut) 0;
	Out.Position =  float4(InPosition, 1.0);//mul(WorldViewProjection, float4(InPosition, 1.0));
	Out.Color 		= float4(InColor, 1.0);
	return Out;
}

float4 PSMain(VertexOut InVar) : SV_TARGET 
{
	return InVar.Color; 
}
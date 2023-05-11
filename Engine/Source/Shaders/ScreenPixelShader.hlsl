
struct VertexOut 
{
    float4 Position : SV_POSITION;
	float3 Normal: NORMAL;
};
float4 PSMain(VertexOut InVar) : SV_TARGET 
{
	return float4(1, 1, 1, 1); 
}
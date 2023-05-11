
struct VertexOut 
{
    float4 Position : SV_POSITION;
	float2 UV: UV;
};

Texture2D Texture;
SamplerState SamplerWrap;
float4 PSMain(VertexOut Input) : SV_TARGET 
{
	return Texture.Sample(SamplerWrap, Input.UV);
}
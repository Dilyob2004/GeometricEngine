struct VertexOut 
{
    float4 Position : SV_POSITION;
	float4 Color: COLOR;
};
float4 PSMain(VertexOut InVar) : SV_TARGET 
{
	return InVar.Color; 
}
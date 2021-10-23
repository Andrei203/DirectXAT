struct VSOut
{	
	float3 color : Color;
	float4 pos: SV_Position;
	
};
//using structure to output position + colour
cbuffer CBuf
{
	matrix transform;
	//indicates 4x4 float
};

VSOut main(float2 pos : Position, float3 color : Color)
{
	VSOut vso;
	//vertices get multipled by shader stage
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), transform);
	vso.color = color;
	return vso;
}
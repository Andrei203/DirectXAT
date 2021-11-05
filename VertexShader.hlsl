/*cbuffer CBuf
{
	matrix model;
	matrix view;
	matrix projection;
};

float4 main(float3 pos : POSITION) : SV_Position
{
	return mul(float4(pos,1.0f),model);
}*/
cbuffer simpleConstantBuffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VertexShaderInput
{
    float3 pos : POSITION;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput vertexShaderOutput;
    float4 pos = float4(input.pos, 1.0f);

    // Transform the vertex position into projection space.
    pos = mul(pos, model);
    pos = mul(pos, view);
    pos = mul(pos, projection);
    vertexShaderOutput.pos = pos;

    return vertexShaderOutput;
}
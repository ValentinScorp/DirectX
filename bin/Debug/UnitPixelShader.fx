
sampler texSampler;

struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;
};

float4 RenderScenePS(	float2 inTexCoord0 : TEXCOORD0) : COLOR0
{
	float4 color = tex2D(texSampler, inTexCoord0);	
	
	return color;
}
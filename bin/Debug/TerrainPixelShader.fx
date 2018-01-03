
sampler texSamplers[5];
sampler TexAlphaSampler;

struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;
};

float2 RotateUv(float2 in_uv, float degree) {

	float2 out_uv;
	float rad = radians(degree);
	
	in_uv -= 0.5;
	
	out_uv.x = in_uv.x * cos(rad) - in_uv.y * sin(rad);
	out_uv.y = in_uv.y * cos(rad) +	in_uv.x * sin(rad);
	
	out_uv += 0.5;
	
	return out_uv;
}

float4 RenderScenePS(	float2 inTexCoord0 : TEXCOORD0,
						float2 inTexCoord1 : TEXCOORD1) : COLOR0
{
	float4 bcolor = tex2D(texSamplers[0], inTexCoord0);
	float4 l1color = tex2D(texSamplers[1], inTexCoord0);	
	float4 l2color = tex2D(texSamplers[2], inTexCoord0);
	float4 l3color = tex2D(texSamplers[3], inTexCoord0);
	float4 l4color = tex2D(texSamplers[4], inTexCoord0);

	float4 alpha1 = tex2D(TexAlphaSampler, inTexCoord1);	
	float4 alpha2 = tex2D(TexAlphaSampler, RotateUv(inTexCoord1, 90));
	float4 alpha3 = tex2D(TexAlphaSampler, RotateUv(inTexCoord1, 180));
	float4 alpha4 = tex2D(TexAlphaSampler, RotateUv(inTexCoord1, 270));
		
	float4 resultColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	resultColor = alpha1 * bcolor + (1.0f - alpha1) * l1color;
	resultColor = alpha2 * resultColor + (1.0f - alpha2) * l2color;
	resultColor = alpha3 * resultColor + (1.0f - alpha3) * l3color;
	resultColor = alpha4 * resultColor + (1.0f - alpha4) * l4color;

	resultColor = saturate(resultColor);
	
	return resultColor;
}
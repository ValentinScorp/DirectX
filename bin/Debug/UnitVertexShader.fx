float4x4 g_mWorldViewProjection;

struct VS_OUTPUT
{
	float4 position : POSITION;
	float4 normal	: NORMAL;
	float2 texCoord0 : TEXCOORD0;	
};

VS_OUTPUT RenderSceneVS(float4 inPosition : POSITION,
	float4 inNormal : NORMAL,
	float2 inTexCoord0 : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.position = mul(inPosition, g_mWorldViewProjection);
	Out.normal = mul(inNormal, g_mWorldViewProjection);
	inNormal = normalize(inNormal);
		
	Out.texCoord0 = inTexCoord0;	

	return Out;
}
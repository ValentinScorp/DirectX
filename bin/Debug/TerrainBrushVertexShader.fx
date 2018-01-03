float4x4 g_mWorldViewProjection;

struct VS_OUTPUT
{
	float4 position : POSITION;	
};

VS_OUTPUT RenderSceneVS(float4 inPosition : POSITION)
{
	VS_OUTPUT Out;

	Out.position = mul(inPosition, g_mWorldViewProjection);	

	return Out;
}
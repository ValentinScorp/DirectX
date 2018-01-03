struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;
};

float4 RenderScenePS() : COLOR0
{
	float4 color = {0.0, 0.5, 0.5, 0.1};	
	
	color.a = 0.5;
	
	return color;
}
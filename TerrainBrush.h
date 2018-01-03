#ifndef SOURCE_TERRAINBRUSH_H_
#define SOURCE_TERRAINBRUSH_H_

#include "Precompiled.h"

struct TERRBRUSHVERTEX {
	FLOAT x, y, z;
	D3DCOLOR diffuse;

};
#define TERRBRUSHFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

class Shader;
class Camera;

class TerrainBrush
{
private:
	float posX = 0;
	float posY = 0;
	float width = 4.0f;

public:
	TerrainBrush(IDirect3DDevice9* dev);
	~TerrainBrush();

	void Render(Camera *camera);

	float GetWidth();
	float GetX();
	float GetY();

	void SetX(float x);
	void SetY(float y);

private:
	Shader *vertexShader;
	Shader *pixelShader;

	IDirect3DDevice9* device;
	IDirect3DVertexDeclaration9 *brushVertexDeclaration = nullptr;
	LPDIRECT3DVERTEXBUFFER9 terrBrushVBuffer = NULL;
};


#endif /* SOURCE_TERRAINBRUSH_H_ */

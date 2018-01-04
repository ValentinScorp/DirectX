#ifndef SOURCE_TERRAINRENDERER_H_
#define SOURCE_TERRAINRENDERER_H_

#include "Precompiled.h"

#define TERRAINFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2)

struct TerrainVertexData {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tcoord0;
	D3DXVECTOR2 tcoord1;
};

class Triangle {
public:
	D3DXVECTOR3 A;
	D3DXVECTOR3 B;
	D3DXVECTOR3 C;
};

class Shader;

class TerrainRenderer
{
private:
	IDirect3DDevice9*	dxDevice = nullptr;
	LPDIRECT3DVERTEXBUFFER9 dxVertexBuffer = nullptr;

	int numVertexes = 0;
	IDirect3DTexture9* sandTex = nullptr;
	IDirect3DTexture9* grassTex = nullptr;
	IDirect3DTexture9* rockTex = nullptr;

	IDirect3DTexture9* alphaSide = nullptr;
	IDirect3DTexture9* alphaCorner = nullptr;
	IDirect3DTexture9* alphaCornerNew = nullptr;
	IDirect3DTexture9* alphaFull = nullptr;
	IDirect3DTexture9* alphaDiag = nullptr;

	std::vector<IDirect3DTexture9*> terrainTextures;
	std::vector<IDirect3DTexture9*> alphaTextures;

	D3DXHANDLE worldViewProjMatrixHandle = 0;

	D3DXCONSTANT_DESC TexAlphaDesc;
	D3DXCONSTANT_DESC texConstantsDesc[5];

	std::vector <Triangle> triangles;
	Terrain *terrain = nullptr;

	Camera *camera = nullptr;
	D3DXMATRIX cameraMatrix;

	IDirect3DVertexDeclaration9 *vertexDeclaration = 0;

	Shader *vertexShaderMy;
	Shader *pixelShaderMy;

public:
	TerrainRenderer(IDirect3DDevice9* dev);
	~TerrainRenderer();

	void Create(std::vector<TerrainPoint> &tpoints);
	void Render();
	void Destroy();
	void SetCamera(Camera *cam);
	void SetTerrain(Terrain *t);
	Terrain *GetTerrain();

	size_t CreateTexture(std::string textureFileName);

};


#endif /* SOURCE_TERRAINRENDERER_H_ */

#include "Precompiled.h"

TerrainRenderer::TerrainRenderer(IDirect3DDevice9* dev)
{
	dxDevice = dev;
	srand(time(NULL));

	vertexShaderMy = new Shader();
	pixelShaderMy = new Shader();
}


TerrainRenderer::~TerrainRenderer()
{
	delete vertexShaderMy;
	delete pixelShaderMy;
}

void TerrainRenderer::Create(std::vector<TerrainPoint>& tpoints)
{
	std::vector<TerrainVertexData> terrainVertexes;
	for (auto tp : tpoints) {
		TerrainVertexData tv;
		tv.position = tp.position;
		tv.normal = tp.normal;
		tv.tcoord0 = tp.textureCo;
		tv.tcoord1 = tp.alphaCo;
		terrainVertexes.push_back(tv);
	}
	numVertexes = terrainVertexes.size();
	dxDevice->CreateVertexBuffer(numVertexes * sizeof(TerrainVertexData), 0, 0, D3DPOOL_MANAGED, &dxVertexBuffer, NULL);
	VOID* pVoid;
	dxVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, &terrainVertexes[0], sizeof(TerrainVertexData) * numVertexes);
	dxVertexBuffer->Unlock();
	D3DXCreateTextureFromFile(dxDevice, "sand.png", &sandTex);
	D3DXCreateTextureFromFile(dxDevice, "grass.png", &grassTex);
	D3DXCreateTextureFromFile(dxDevice, "rock.png", &rockTex);
	D3DXCreateTextureFromFile(dxDevice, "alphaSide.png", &alphaSide);
	D3DXCreateTextureFromFile(dxDevice, "alphaCorner.png", &alphaCorner);
	D3DXCreateTextureFromFile(dxDevice, "alphaCornerNew.png", &alphaCornerNew);
	D3DXCreateTextureFromFile(dxDevice, "alphaDiag.png", &alphaDiag);

	terrainTextures.push_back(rockTex);
	terrainTextures.push_back(grassTex);
	terrainTextures.push_back(sandTex);
	terrainTextures.push_back(rockTex);
	terrainTextures.push_back(rockTex);

	HRESULT hr;
	ID3DXBuffer *pErrors = nullptr;
	hr = D3DXCreateBuffer(1024, &pErrors);

	if (FAILED(hr)) {
		// Output shader compilation errors to the shell:
		CHAR* pErrorStr = (CHAR*)pErrors->GetBufferPointer();
		printf("%s\n", pErrorStr);
	}
	if (pErrors) {
		pErrors->Release();
		pErrors = nullptr;
	}

	D3DVERTEXELEMENT9 decl[] = {
			{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
			{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			{0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
			D3DDECL_END()
	};
	dxDevice->CreateVertexDeclaration(decl, &vertexDeclaration);

	vertexShaderMy->CreateVertexShader(dxDevice, "TerrainVertexShader.fx", "RenderSceneVS");
	vertexShaderMy->PrepareMatrix("g_mWorldViewProjection");

	pixelShaderMy->CreatePixelShader(dxDevice, "TerrainPixelShader.fx", "RenderScenePS");
	pixelShaderMy->PrepareTexture("TexAlphaSampler");
	pixelShaderMy->PrepareTextureArray("texSamplers");
}

void TerrainRenderer::Render()
{
	D3DXMATRIX matTransform;
	D3DXMatrixIdentity(&matTransform);
	dxDevice->SetTransform(D3DTS_WORLD, &matTransform);
	dxDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	D3DXMatrixIdentity(&cameraMatrix);

	D3DXMATRIX matView = camera->GetTransformMatrix();
	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection, D3DXToRadian(camera->GetFovy()), (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, camera->GetNearPlane(), camera->GetFarPlane());

	cameraMatrix = matView * matProjection;

	dxDevice->SetVertexDeclaration(vertexDeclaration);

	dxDevice->SetStreamSource(0, dxVertexBuffer, 0, sizeof(TerrainVertexData));

	vertexShaderMy->Activate();
	vertexShaderMy->SetMatrix(&cameraMatrix);

	pixelShaderMy->Activate();

	for (size_t i = 0; i < terrain->tiles.size(); i++) {
		if (terrain->tiles[i].GetTextureAlpha() == 0)
			pixelShaderMy->SetTexture(alphaCorner);
		else {
			pixelShaderMy->SetTexture(alphaCornerNew);
		}

		std::vector<IDirect3DTexture9*> terrTex;
		for (size_t j = 0; j < 5; j++) {
			terrTex.push_back(terrainTextures[terrain->tiles[i].GetTexture(j)]);
		}
		pixelShaderMy->SetArrayTexture(&terrTex);
		dxDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i * 6, 2);
	}

	dxDevice->SetVertexShader(0);
	dxDevice->SetPixelShader(0);
}

void TerrainRenderer::Destroy()
{
	if (sandTex) {
		sandTex->Release();
		sandTex = nullptr;
	}
	if (grassTex) {
		grassTex->Release();
		grassTex = nullptr;
	}
	if (rockTex) {
		rockTex->Release();
		rockTex = nullptr;
	}
	if (alphaSide) {
		alphaSide->Release();
		alphaSide = nullptr;
	}
	if (alphaCorner) {
		alphaCorner->Release();
		alphaCorner = nullptr;
	}
	if (alphaFull) {
		alphaCorner->Release();
		alphaCorner = nullptr;
	}
	if (alphaDiag) {
		alphaDiag->Release();
		alphaDiag = nullptr;
	}

	if (dxVertexBuffer) {
		dxVertexBuffer->Release();
		dxVertexBuffer = NULL;
	}

	vertexShaderMy->Destroy();
	pixelShaderMy->Destroy();
}

void TerrainRenderer::SetCamera(Camera * cam)
{
	camera = cam;
}

void TerrainRenderer::SetTerrain(Terrain * t)
{
	terrain = t;
}

Terrain* TerrainRenderer::GetTerrain() {
	return terrain;
}

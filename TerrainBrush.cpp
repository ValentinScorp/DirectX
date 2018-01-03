#include "Precompiled.h"

TerrainBrush::TerrainBrush(IDirect3DDevice9* dev)
{
	device = dev;

	D3DVERTEXELEMENT9 decl1[] = {
				{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
				//{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
				D3DDECL_END()
	};

	device->CreateVertexDeclaration(decl1, &brushVertexDeclaration);

	device->CreateVertexBuffer(6 * sizeof(TERRBRUSHVERTEX),
				D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, TERRBRUSHFVF, D3DPOOL_DEFAULT, &terrBrushVBuffer, NULL);

	vertexShader = new Shader();
	pixelShader = new Shader();

	vertexShader->CreateVertexShader(device, "TerrainVertexShader.fx", "RenderSceneVS");

	vertexShader->PrepareMatrix("g_mWorldViewProjection");

	pixelShader->CreatePixelShader(device, "TerrainBrushPixelShader.fx", "RenderScenePS");
}


TerrainBrush::~TerrainBrush()
{
	delete vertexShader;
	delete pixelShader;

	if (terrBrushVBuffer) {
		terrBrushVBuffer->Release();
		terrBrushVBuffer = NULL;
	}
}

float TerrainBrush::GetWidth()
{
	return width;
}

float TerrainBrush::GetX()
{
	return posX;
}

float TerrainBrush::GetY()
{
	return posY;
}

void TerrainBrush::SetX(float x)
{
	int w = width;
	int newx = (((int)x + w / 2) / w) * w;

	posX = newx;
}

void TerrainBrush::SetY(float y)
{
	int w = width;
	int newy = (((int)y + w / 2) / w) * w;
	posY = newy;
}



void TerrainBrush::Render(Camera *camera) {
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	device->SetVertexDeclaration(brushVertexDeclaration);
	device->SetStreamSource(0, terrBrushVBuffer, 0, sizeof(TERRBRUSHVERTEX));

	float hw = width / 2.0f;

	TERRBRUSHVERTEX tbVerts[] = {
		{ -hw, -hw, 0.01f },
		{ hw, hw, 0.01f },
		{ -hw, hw, 0.01f },

		{ -hw, -hw, 0.01f },
		{ hw, -hw, 0.01f },
		{ hw, hw, 0.01f },
	};

	D3DXMATRIX matView = camera->GetTransformMatrix();
	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection, D3DXToRadian(camera->GetFovy()), (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, camera->GetNearPlane(), camera->GetFarPlane());

	D3DXMATRIX worldMatrix;
	D3DXMatrixTranslation(&worldMatrix, posX, posY, 0.1);
	D3DXMATRIX cameraMatrix = worldMatrix * matView * matProjection;

	vertexShader->Activate();
	vertexShader->SetMatrix(&cameraMatrix);

	pixelShader->Activate();

	VOID *pVoid = nullptr;
	terrBrushVBuffer->Lock(0, 6 * sizeof(TERRBRUSHVERTEX), (void**)&pVoid, D3DLOCK_DISCARD);
	memcpy(pVoid, tbVerts, 6 * sizeof(TERRBRUSHVERTEX));
	terrBrushVBuffer->Unlock();

	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	device->SetVertexShader(0);
	device->SetPixelShader(0);
}

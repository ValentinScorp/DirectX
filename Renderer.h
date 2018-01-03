#ifndef SOURCE_RENDERER_H_
#define SOURCE_RENDERER_H_

#include "Precompiled.h"

struct CUSTOMVERTEX {
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
	FLOAT    tu, tv;
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

class RenderObject {
public:
	RenderObject():
		mesh(nullptr), rbody(nullptr)
	{
	}
	~RenderObject() {}

	Mesh* mesh;
	RigidBody* rbody;
};

class Clock;
class GuiBitmap;

class Renderer : public MessageReceiver
{
public:
	Renderer(Camera *cam);

	void Initialize(HWND hWnd);
	void InitializeLightAndMaterials();

	void AddTerrainBrush(TerrainBrush *tb);
	void AddVertexes(CUSTOMVERTEX *vertexes, int vertexesNumb);
	void AddIndexes(int *indexes, int indexesNumb);
	//void SetUserInput(UserInput *up);

	void AttachMesh(Mesh *m);
	void AllocateVideoMemory();

	size_t CreateTexture(std::string fileName);
	void AttachCamera(Camera *cam);

	void AddGameObject(GameObject *go);

	void BeginScene();
	void Draw();
	void EndScene();

	TerrainRenderer* GetTerrainRenderer() {
		return terrainRenderer;
	}
	void SetCamera(Camera *cam);

	IDirect3DDevice9* GetDevice();

	void Destroy();
	Message::State OnMessage(Message mess);

	virtual ~Renderer();

private:
	GuiBitmap*			guiBitmap = nullptr;
	IDirect3D9*			pDirect3D = nullptr;
	IDirect3DDevice9*	pDevice = nullptr;
	IDirect3DVertexDeclaration9 *vertexDeclaration = nullptr;

	TerrainRenderer*	terrainRenderer = nullptr;

	std::vector<IDirect3DTexture9*> textures;

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;

	std::vector <GameObject*> *graph_objects = nullptr;
	std::list <Mesh*> meshes;
	std::list <RenderObject*> robjects;

	Camera *camera;
	int oldX = 0;
	int oldY = 0;

	TerrainBrush *terrainBrush = nullptr;
	float index = 0.0f;

	Clock *clock = 0;
};



#endif

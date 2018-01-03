#include "Precompiled.h"

#ifndef SOURCE_MESH_H_
#define SOURCE_MESH_H_

class DxVertex {
public:
	DxVertex() {}
	~DxVertex() {}

	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

class Mesh
{
protected:
	std::vector<DxVertex> vertexes;
	std::string textureFileName = "default.png";
	size_t textureId = 0;

public:
	Mesh();
	virtual ~Mesh();

	virtual void addVertex(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 uv);
	virtual void addVertex(DxVertex ver);
	virtual void UpdateAnimation(float dt);
	void SetTexture(std::string fileName);
	void SetTextureId(size_t id);
	std::string GetTexture();
	size_t GetTextureId();

	virtual size_t GetVertexesNum();
	virtual size_t GetVertexSize();
	virtual DxVertex* GetVertexes();
};
#endif /* SOURCE_MESH_H_ */

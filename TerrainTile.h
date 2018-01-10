#ifndef SOURCE_TERRAINTILE_H_
#define SOURCE_TERRAINTILE_H_

struct TerrainPoint {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 textureCo;
	D3DXVECTOR2 alphaCo;
};

class TerrainTile
{
private:

	struct Triangle {
		TerrainPoint A;
		TerrainPoint B;
		TerrainPoint C;
	};

	std::vector <TerrainPoint> points;

	Triangle triangle1;
	Triangle triangle2;

	size_t textureIndexes[5];
	size_t textureAlpha = 0;

public:

	TerrainTile(TerrainPoint point1, TerrainPoint point2, TerrainPoint point3, TerrainPoint point4);
	~TerrainTile();

	bool Intersection(RayVector ray, D3DXVECTOR3 &intersectionVertex);

	std::vector <TerrainPoint> & GetPoints();
	void ClearPoints();

	bool IsPointOnTile(D3DXVECTOR3 p);

	void SetTexFront(size_t textureIndex);
	void SetTexBack(size_t textureIndex);
	void SetTexAlpha(size_t texIndex);
	void SetAlphaRotaion(int arot);
	void PrintSelf();

	void SetTexture(size_t index, size_t num);
	void SetBaseTexture(size_t index);
	size_t GetTexture(size_t num);
	size_t GetTextureAlpha();

private:
	bool intersectRayTriangle(RayVector ray, Triangle triangle, D3DXVECTOR3 &intersectionVertex);



};

#endif /* SOURCE_TERRAINTILE_H_ */

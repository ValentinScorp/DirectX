#ifndef SOURCE_TERRAIN_H_
#define SOURCE_TERRAIN_H_

class TerrainRenderer;

class Terrain
{
private:

	TerrainRenderer *terrainRenderer = nullptr;

	int width;
	int height;
	int patchDimention;
	float tile;

	int currentBrushType = 0;
public:
	std::vector <TerrainTile> tiles;

	Terrain(int w, int h, float t);
	~Terrain();

	void CreateGraphics(TerrainRenderer *tr);

	void SetTilesSurface(D3DXVECTOR3 point);
	void SetBrushType(int brushType);
	void saveMap();
	void loadMap();
	void generateMap();

	D3DXVECTOR3 GetTerraneIntersection(RayVector rv);
};



#endif /* SOURCE_TERRAIN_H_ */

#ifndef SOURCE_TERRAINPATCH_H_
#define SOURCE_TERRAINPATCH_H_

class TerrainPatch
{
private:
	std::vector <TerrainTile> tiles;

public:
	TerrainPatch(int x, int y, int tilesDim, float tileSize);
	~TerrainPatch();

	std::vector <TerrainTile> & GetTiles();
};
#endif /* SOURCE_TERRAINPATCH_H_ */

#include "Precompiled.h"

Terrain::Terrain(int w, int h, float t)
{
	width = w;
	height = h;
	patchDimention = 4;
	tile = t;
}

Terrain::~Terrain()
{
}

void Terrain::CreateGraphics(TerrainRenderer * tr)
{
    terrainRenderer = tr;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			TerrainPatch patch(i, j, patchDimention, tile);
			std::vector<TerrainTile> ptiles = patch.GetTiles();
			tiles.insert(tiles.end(), ptiles.begin(), ptiles.end());
		}
	}
	std::vector <TerrainPoint> tp;

	for (auto t : tiles) {
		auto points = t.GetPoints();
		for (auto p : points) {
			tp.push_back(p);
		}
		t.ClearPoints();
	}
	terrainRenderer->Create(tp);
}

D3DXVECTOR3 Terrain::GetTerraneIntersection(RayVector rv)
{
	D3DXVECTOR3 intersection = { 0.0f, 0.0f, 0.0f };

	for (auto t : tiles) {
		if (t.Intersection(rv, intersection)) {
			return intersection;
		}
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Terrain::SetTilesSurface(D3DXVECTOR3 point) {
	D3DXVECTOR3 point2(point.x + 2.0f, point.y - 2.0f, 0.0);
	D3DXVECTOR3 point1(point.x - 2.0f, point.y - 2.0f, 0.0);
	D3DXVECTOR3 point3(point.x - 2.0f, point.y + 2.0f, 0.0);
	D3DXVECTOR3 point4(point.x + 2.0f, point.y + 2.0f, 0.0);

	for (TerrainTile &tile : tiles) {
		if (tile.IsPointOnTile(point1))
			tile.SetTexture(currentBrushType, 2);
		if (tile.IsPointOnTile(point2))
			tile.SetTexture(currentBrushType, 1);
		if (tile.IsPointOnTile(point3))
			tile.SetTexture(currentBrushType, 3);
		if (tile.IsPointOnTile(point4))
			tile.SetTexture(currentBrushType, 4);
	}
}

void Terrain::SetBrushType(int brushType) {
    if (brushType >=0 && brushType <= 2) {
        currentBrushType = brushType;
    }
}

void Terrain::saveMap()
{
    std::ofstream outFile("map.dat", std::ios::out | std::ios::binary);
    outFile.write((char*)&tiles[0], tiles.size() * sizeof(TerrainTile));
    outFile.close();
}

void Terrain::loadMap()
{
    terrainRenderer->Destroy();
    tiles.clear();
}

void Terrain::generateMap()
{
    terrainRenderer->Destroy();
    tiles.clear();

    CreateGraphics(terrainRenderer);
}

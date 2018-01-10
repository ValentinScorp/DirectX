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
			TerrainPatch patch(j, i, patchDimention, tile);
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

    for (TerrainTile &tile : tiles) {
        outFile << tile.GetTexture(0);
        outFile << tile.GetTexture(1);
        outFile << tile.GetTexture(2);
        outFile << tile.GetTexture(3);
        outFile << tile.GetTexture(4);
    }

    outFile.close();
}

void Terrain::loadMap()
{
    generateMap();

    std::ifstream inFile("map.dat", std::ios::in | std::ios::binary);

    inFile.seekg(0, std::ios::end);
	long fileSize = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	unsigned char *data = new unsigned char[fileSize];
	inFile.read((char*)data, fileSize);
	inFile.close();

	unsigned char *data_iterator = data;
    char textures[5];

    size_t totalPatches = fileSize / 5 / sizeof(char);

    for (size_t i = 0; i < totalPatches; i++) {
        memcpy(textures, data_iterator, sizeof(char) * 5);
        tiles[i].SetTexture(textures[1]-'0', 1);
        tiles[i].SetTexture(textures[2]-'0', 2);
        tiles[i].SetTexture(textures[3]-'0', 3);
        tiles[i].SetTexture(textures[4]-'0', 4);
        tiles[i].SetBaseTexture(textures[0]-'0');

        data_iterator += sizeof(char) * 5;
    }

    delete data;
}

void Terrain::generateMap()
{
    terrainRenderer->Destroy();
    tiles.clear();

    CreateGraphics(terrainRenderer);
}

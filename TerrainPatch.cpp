#include "Precompiled.h"


TerrainPatch::TerrainPatch(int x, int y, int tilesDim, float tileSize)
{
	float xPos = x * tileSize * tilesDim;
	float yPos = y * tileSize * tilesDim;

	float k = 1.0f / tilesDim;

	for (int i = 0; i < tilesDim; i++) {
		for (int j = 0; j < tilesDim; j++) {

			TerrainPoint tp1, tp2, tp3, tp4;

			tp1.position = { xPos + j * tileSize, yPos + i * tileSize, 0.0f };
			tp2.position = { xPos + j * tileSize, yPos + (i + 1) * tileSize, 0.0f };
			tp3.position = { xPos + (j + 1) * tileSize, yPos + (i + 1) * tileSize, 0.0f };
			tp4.position = { xPos + (j + 1) * tileSize, yPos + i * tileSize, 0.0f };

			tp1.textureCo.x = j * k;
			tp1.textureCo.y = i * k;

			tp2.textureCo.x = j * k;
			tp2.textureCo.y = (i * k + k);

			tp3.textureCo.x = (j * k + k);
			tp3.textureCo.y = (i * k + k);

			tp4.textureCo.x = (j * k + k);
			tp4.textureCo.y = i * k;

			TerrainTile t(tp1, tp2, tp3, tp4);

			tiles.push_back(t);
		}
	}
}

TerrainPatch::~TerrainPatch()
{
}

std::vector<TerrainTile>& TerrainPatch::GetTiles()
{
	return tiles;
}

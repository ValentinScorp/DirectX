#include "Precompiled.h"

TerrainTile::TerrainTile(TerrainPoint point1, TerrainPoint point2, TerrainPoint point3, TerrainPoint point4)
{
	triangle1.A.position = point1.position;
	triangle1.B.position = point3.position;
	triangle1.C.position = point2.position;

	triangle2.A.position = point1.position;
	triangle2.B.position = point4.position;
	triangle2.C.position = point3.position;

	triangle2.C.normal.x = 0;
	triangle2.C.normal.y = 0;
	triangle2.C.normal.z = 1;
	triangle1.A.normal = triangle1.B.normal = triangle1.C.normal = triangle2.A.normal = triangle2.B.normal = triangle2.C.normal;


	triangle1.A.alphaCo.x = 0; triangle1.A.alphaCo.y = 0;
	triangle1.B.alphaCo.x = 1; triangle1.B.alphaCo.y = 1;
	triangle1.C.alphaCo.x = 0; triangle1.C.alphaCo.y = 1;

	triangle2.A.alphaCo.x = 0; triangle2.A.alphaCo.y = 0;
	triangle2.B.alphaCo.x = 1; triangle2.B.alphaCo.y = 0;
	triangle2.C.alphaCo.x = 1; triangle2.C.alphaCo.y = 1;

	triangle1.A.textureCo = point1.textureCo;
	triangle1.B.textureCo = point3.textureCo;
	triangle1.C.textureCo = point2.textureCo;

	triangle2.A.textureCo = point1.textureCo;
	triangle2.B.textureCo = point4.textureCo;
	triangle2.C.textureCo = point3.textureCo;

	for (size_t i = 0; i < 5; i++) {
		textureIndexes[i] = 0;
	}
	textureAlpha = rand() % 2;
}

TerrainTile::~TerrainTile()
{
}

bool TerrainTile::Intersection(RayVector ray, D3DXVECTOR3 & intersectionVertex)
{
	return intersectRayTriangle(ray, triangle1, intersectionVertex) | intersectRayTriangle(ray, triangle2, intersectionVertex);
}

std::vector<TerrainPoint>& TerrainTile::GetPoints()
{
	points.push_back(triangle1.A);
	points.push_back(triangle1.B);
	points.push_back(triangle1.C);

	points.push_back(triangle2.A);
	points.push_back(triangle2.B);
	points.push_back(triangle2.C);

	return points;
}

void TerrainTile::ClearPoints()
{
	points.clear();
}

bool TerrainTile::intersectRayTriangle(RayVector ray, Triangle triangle, D3DXVECTOR3 &intersectionVertex)
{
	// находим вектора сторон треугольника
	D3DXVECTOR3 u = triangle.B.position - triangle.A.position;
	D3DXVECTOR3 v = triangle.C.position - triangle.A.position;

	// находим нормаль к треугольнику
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);

	if (n.x == 0 && n.y == 0 && n.z == 0) {
		return 0;                       // неверные параметры треугольника (либо точки на одной прямой, либо все в одной точке)
	}

	// вектор направления луча
	D3DXVECTOR3 dir = ray.end - ray.begin;
	// векор от точки на треугольнике до начала луча
	D3DXVECTOR3 w0 = ray.begin - triangle.A.position;

	float a = -D3DXVec3Dot(&n, &w0);
	float b = D3DXVec3Dot(&n, &dir);

	if (fabs(b) < 0.0001) {       // луч паралельный плоскости треугольника
		if (a == 0) { return 0; }   // луч лежит на плоскости треугольника
		else { return 0; }   // луч не на плоскости треугольника

	}
	// найдем точку пересечения луча с треугольником
	float r = a / b;
	if (r < 0.0) {
		return 0;                    // луч идет мимо треугольника
	}
	// для сегмента проверить также (r > 1.0) => нет пересечения

	intersectionVertex = ray.begin + dir * r;           // точка пересечения луча и плоскости
														// лежит ли точка в треугольнике
	float    uu, uv, vv, wu, wv, D;
	uu = D3DXVec3Dot(&u, &u);
	uv = D3DXVec3Dot(&u, &v);
	vv = D3DXVec3Dot(&v, &v);
	D3DXVECTOR3 w = intersectionVertex - triangle.A.position;
	wu = D3DXVec3Dot(&w, &u);
	wv = D3DXVec3Dot(&w, &v);
	D = uv * uv - uu * vv;

	// найдем и проверим параметрические координаты
	float s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0) {
		return 0;                   // точка вне треугольника
	}
	float t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0) {
		return 0;                   // точка вне треугольника
	}

	return 1;
}

void TerrainTile::SetTexture(size_t index, size_t num) {
	textureIndexes[num] = index;
	textureIndexes[0] = index;
}
void TerrainTile::SetBaseTexture(size_t index)
{
    textureIndexes[0] = index;
}

size_t TerrainTile::GetTexture(size_t num) {
	return textureIndexes[num];
}

bool TerrainTile::IsPointOnTile(D3DXVECTOR3 p) {
	if ((p.x > triangle1.A.position.x && p.x < triangle1.B.position.x) &&
			(p.y > triangle1.A.position.y && p.y < triangle1.B.position.y) ) {
		return 1;
	}
	return 0;
}

void TerrainTile::PrintSelf() {
	std::cout << triangle1.A.position.x << " x " << triangle1.A.position.y << std::endl;
}

size_t TerrainTile::GetTextureAlpha() {
	return textureAlpha;
}


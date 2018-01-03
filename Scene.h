#include "Precompiled.h"

#ifndef SOURCE_SCENE_H_
#define SOURCE_SCENE_H_

class Renderer;
class Terrain;

class Scene : public MessageReceiver
{
public:
	Scene();
	virtual ~Scene();

	void Initialize(Renderer *r);
	Message::State OnMessage(Message mes);

	void UpdateUnits(float dt);
	Camera* GetActiveCamera();

	GameObject* GetGameObject(std::string oname);

	void Destroy();
private:
	Renderer *renderer = nullptr;
	std::vector <GameObject*> objects;
	Terrain *terrain = nullptr;
	Camera *camera;
	//TerrainBrush *terrainBrush = nullptr;
	bool tmpRun = 0;
};

#endif /* SOURCE_SCENE_H_ */

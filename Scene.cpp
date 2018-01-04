#include "Precompiled.h"

Scene::Scene()
{
	camera = 0;
}

void Scene::Initialize(Renderer *r)
{
	tmpRun = 0;

	camera = new Camera(D3DXVECTOR3(0, -10, 15), D3DXVECTOR3(-45, 180, 0));

	terrain = new Terrain(16, 16, 4.0f);
	terrain->CreateGraphics(r->GetTerrainRenderer());

	r->GetTerrainRenderer()->SetCamera(camera);
	r->GetTerrainRenderer()->SetTerrain(terrain);
	renderer = r;

	SmaLoader smaLoader;

	GameObject *man = smaLoader.load("Cube.002.sma");
	RigidBody* manBody = new RigidBody();
	man->SetRigidBody(manBody);

	GameObject *arrow = smaLoader.load("arrow.sma");
	RigidBody* arrowBody = new RigidBody();
	arrow->SetRigidBody(arrowBody);

	if (man != nullptr)
		objects.push_back(man);

	if (arrow != nullptr)
		objects.push_back(arrow);

	renderer->AddGameObject(man);
	renderer->AddGameObject(arrow);

	renderer->AllocateVideoMemory();
}

Message::State Scene::OnMessage(Message mes)
{
    Message::State messageState = Message::MS_NOT_HANDLED;

	if (mes.type == "user_input" && mes.name == "left_mouse_button_down") {
		RayVector camRay = camera->GetVectorRay(mes.x, mes.y);
		D3DXVECTOR3 intersection = terrain->GetTerraneIntersection(camRay);
		for (GameObject* go : objects) {
			if (go->name == "Arrow") {
				go->SetPosition(intersection);
			}
			if (go->name == "Cube.002") {
				go->SetCommand(new MoveUnitCommand(go, intersection));
			}
		}
		terrain->SetTilesSurface(intersection);

		messageState = Message::MS_HANDLED;
	}

	if (mes.type == "user_input" && mes.name == "a") {
		tmpRun = !tmpRun;
		GameObject *go = GetGameObject("Cube.002");
		tmpRun ? go->StartAnimation("Walk") : go->StopAnimation();
		messageState = Message::MS_HANDLED;
	}
	if (mes.type == "gui_message" && mes.name == "change_brush_texture") {
		terrain->SetBrushType(mes.delta);
		messageState = Message::MS_HANDLED;
	}
	if (mes.type == "gui_message" && mes.name == "map_manipulation") {
        if (mes.delta == 3) {
            terrain->saveMap();
        }
        if (mes.delta == 4) {
            terrain->loadMap();
        }
        if (mes.delta == 5) {
            terrain->generateMap();
        }
        messageState = Message::MS_HANDLED;
	}
    return messageState;
}

void Scene::UpdateUnits(float dt)
{
	for (GameObject *go : objects) {
		go->Update(dt);
	}
}

Camera * Scene::GetActiveCamera()
{
	return camera;
}

GameObject * Scene::GetGameObject(std::string oname)
{
	for (auto go : objects) {
		if (go->GetName() == oname) {
			return go;
		}
	}
	return nullptr;
}

void Scene::Destroy()
{
	for (GameObject *object : objects) {
		if (object != nullptr) {
			delete object;
		}
		object = nullptr;
	}
	objects.clear();

	if (terrain != nullptr) {
		delete terrain;
	}

}


Scene::~Scene()
{
	if (camera != 0) {
		delete camera;
	}
}

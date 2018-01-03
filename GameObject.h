#include "Precompiled.h"

#ifndef SOURCE_GAMEOBJECT_H_
#define SOURCE_GAMEOBJECT_H_

class GameObject;
class AnimatedMesh;

struct VertexData {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

class UnitCommand {
protected:
	GameObject *gameobject;
	std::string animationName;
	bool complete;

public:

	UnitCommand(GameObject *go, std::string aname)
		: gameobject(go), animationName(aname), complete(0) {}
	virtual ~UnitCommand(){}

	virtual void Update() = 0;

	bool IsComplete() {
		return complete;
	}
	std::string GetAnimationName() {
		return animationName;
	}
};

class MoveUnitCommand : public UnitCommand {
private:
	D3DXVECTOR3 orientationVector;
	D3DXVECTOR3 destination;
	float speed;

public:
	MoveUnitCommand(GameObject *go, D3DXVECTOR3 dest);
	~MoveUnitCommand(){}

	void Update();
};

class GameObject
{
public:
	std::string name;

	Mesh *mesh;
	AnimatedMesh *animatedMesh;
	RigidBody *rigidBody;

	std::vector<D3DXVECTOR3> vertPositionsInit;
	std::vector<VertexData> vertexes;
	std::vector<int> indexes;

	int animationFrame;
	float animationSpeed;

	UnitCommand *command;

public:
	GameObject();
	~GameObject();

	void AddVertex(VertexData vd);
	void AddIndex(int i);

	int* GetIndexes() {
		return &indexes[0];
	}

	VertexData* GetVertexes() {
		return &vertexes[0];
	}

	unsigned int GetIndexNum() {
		return indexes.size();
	}
	unsigned int GetVertexNum() {
		return vertexes.size();
	}

	void AddMesh(Mesh *m);
	Mesh* GetMesh();
	Mesh* GetAnimatedMesh();
	RigidBody* GetRigidBody();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);

	void SetCommand(UnitCommand *com);
	void Update(float dt);

	void animate();

	void SetMesh(Mesh *m);
	void SetRigidBody(RigidBody *rb);

	void SetAnimatedMesh(AnimatedMesh *am);
	void StartAnimation(std::string aname);
	void StopAnimation();

	std::string GetName();

};

#endif /* SOURCE_GAMEOBJECT_H_ */

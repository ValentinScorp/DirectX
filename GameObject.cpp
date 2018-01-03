#include "Precompiled.h"

GameObject::GameObject()
{
	animationFrame = 0;
	animationSpeed = 0.1;
	command = 0;

	mesh = nullptr;
	animatedMesh = nullptr;
	rigidBody = nullptr;
}

GameObject::~GameObject()
{
	if (command != 0) {
		delete command;
	}
	if (animatedMesh != nullptr) {
		delete animatedMesh;
	}
	if (mesh != nullptr) {
		delete mesh;
	}
	if (rigidBody != nullptr) {
		delete rigidBody;
	}
}

void GameObject::AddVertex(VertexData vd)
{
	vertexes.push_back(vd);
}

void GameObject::AddIndex(int i)
{
	indexes.push_back(i);
}

void GameObject::AddMesh(Mesh * m)
{
	if (m != 0) {
		mesh = m;
	}
}

RigidBody * GameObject::GetRigidBody()
{
	return rigidBody;
}

Mesh* GameObject::GetMesh() {
	return mesh;
}

Mesh * GameObject::GetAnimatedMesh()
{
	return (Mesh*)animatedMesh;
}

D3DXVECTOR3 GameObject::GetPosition()
{
	if (rigidBody != nullptr) {
		return rigidBody->GetPosition();
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void GameObject::SetPosition(D3DXVECTOR3 pos)
{
	if (rigidBody != nullptr) {
		rigidBody->SetPosition(pos);
	}
}

void GameObject::SetCommand(UnitCommand * com)
{
	if (command != 0) {
		delete command;
		command = 0;
	}
	command = com;
	animatedMesh->BeginAnimation(command->GetAnimationName());
}

void GameObject::Update(float dt)
{
	animationSpeed += 1;
	if (animationSpeed >= 1) {
		animationSpeed = 0;
		animationFrame++;
	}
	if (animationFrame >= 31) {
		animationFrame = 0;
	}

	if (command != 0) {
		if (command->IsComplete()) {
			delete command;
			command = 0;
			animatedMesh->StopAnimation();
		}
		else {
			command->Update();
			animatedMesh->UpdateAnimation(1);
		}
	}



	//animations->AnimateMesh(animatedMesh, mesh, "Walk", animationFrame);


}

void GameObject::animate()
{
}


void GameObject::SetMesh(Mesh * m)
{
	mesh = m;
}

void GameObject::SetRigidBody(RigidBody * rb)
{
	rigidBody = rb;
}

void GameObject::SetAnimatedMesh(AnimatedMesh * am)
{
	animatedMesh = am;
}

void GameObject::StopAnimation()
{
	animatedMesh->StopAnimation();
}

void GameObject::StartAnimation(std::string aname)
{
	animatedMesh->BeginAnimation(aname);
}

std::string GameObject::GetName()
{
	return name;
}

MoveUnitCommand::MoveUnitCommand(GameObject *go, D3DXVECTOR3 dest)
	: UnitCommand(go, "Walk"), destination(dest), speed(0.3)
{
	//orientationVector = destination - go->GetPosition();
	orientationVector = go->GetPosition() - destination;
	D3DXVec3Normalize(&orientationVector, &orientationVector);
}

void MoveUnitCommand::Update()
{
	if (complete == 1) {
		return;
	}

	gameobject->GetRigidBody()->SetOrientationVector(orientationVector);

	D3DXVECTOR3 delta = destination - gameobject->GetPosition();

	float lengthToTarget = D3DXVec3Length(&delta);

	float xsign = 1;
	float ysign = 1;
	if (delta.x < 0)
		xsign = -1;
	if (delta.y < 0)
		ysign = -1;
	if (delta.x != 0) {
		float tang = abs(delta.y / delta.x);
		float rotation = atan(tang);
		delta.x = cos(rotation) * xsign;
		delta.y = sin(rotation) * ysign;
	}

	if (delta.x == 0) {
		delta.x = 1;
		delta.y = 0;
	}
	if (delta.y == 0) {
		delta.x = 0;
		delta.y = 1;
	}
	if (lengthToTarget > (D3DXVec3Length(&delta) * speed)) {
		gameobject->SetPosition(gameobject->GetPosition() + delta * speed);
	}
	else
	{
		complete = 1;
	}
}


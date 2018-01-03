#include "Precompiled.h"

RigidBody::RigidBody():
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f)
{
	orientation = { 1.0f,	0.0f,	0.0f,	0.0f,
					0.0f,	1.0f,	0.0f,	0.0f,
					0.0f,	0.0f,	1.0f,	0.0f,
					position.x,		position.y,		position.z,		1.0f };
}

RigidBody::~RigidBody()
{
}

void RigidBody::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;

	orientation._41 = position.x;
	orientation._42 = position.y;
	orientation._43 = position.z;
}

D3DXVECTOR3 RigidBody::GetPosition()
{
	return position;
}

D3DXMATRIX RigidBody::GetTransformationMatrix()
{
	return orientation;
}

void RigidBody::SetOrientationVector(D3DXVECTOR3 ovec)
{
	D3DXVECTOR3 upVector(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 sideVector;
	D3DXVec3Cross(&sideVector, &upVector, &ovec);

	D3DXVec3Normalize(&sideVector, &sideVector);

	orientation = { -sideVector.x,	-sideVector.y,	-sideVector.z,	0.0f,
					ovec.x,			ovec.y,			ovec.z,			0.0f,
					upVector.x,		upVector.y,		upVector.z,		0.0f,
					position.x,		position.y,		position.z,		1.0f };
}


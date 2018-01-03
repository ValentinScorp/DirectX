/*
 * Camera.h
 *
 *  Created on: 8 лист. 2017 р.
 *      Author: Valentin
 */

#ifndef SOURCE_CAMERA_H_
#define SOURCE_CAMERA_H_

class RayVector {
public:
	RayVector() {
		begin = {0.0f, 0.0f, 0.0f};
		end = { 0.0f, 0.0f, 0.0f };
	}
	RayVector(D3DXVECTOR3 b, D3DXVECTOR3 e) {
		begin = { b.x, b.y, b.z };
		end = { e.x, e.y, e.z };
	}
	~RayVector() {}
	D3DXVECTOR3 begin;
	D3DXVECTOR3 end;
};

class Camera : public MessageReceiver
{
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	float fovy = 0;
	float nearPlane = 0;
	float farPlane = 0;

	int startX = 0;
	int startY = 0;
	bool movingXZ = 0;
	bool movingXY = 0;

	D3DXVECTOR3 camRayBegin;
	D3DXVECTOR3 camRayEnd;
public:
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	virtual ~Camera();

	D3DXVECTOR3 GetPosition() {
		return position;
	}
	D3DXVECTOR3 GetRotation() {
		return rotation;
	}
	void moveUp(float delta) {
		position.z += delta;
	}
	void moveDown(float delta) {
		position.z -= delta;
	}
	void moveLeft(float delta) {
		position.x += delta;
	}
	void moveRight(float delta) {
		position.x -= delta;
	}
	void moveForward(float delta) {
		position.y += delta;
	}
	void moveBackward(float delta) {
		position.y -= delta;
	}
	void StartMoveXZ(int x, int y) {
		startX = x;
		startY = y;
		movingXZ = 1;
	}
	void StopMoveXZ() {
		startX = 0;
		startY = 0;
		movingXZ = 0;
	}

	float GetFovy() {
		return fovy;
	}
	float GetNearPlane() {
		return nearPlane;
	}
	float GetFarPlane() {
		return farPlane;
	}

	void UpdatePositionXZ(int deltaX, int deltaZ) {
		if (movingXZ) {
			position.x += deltaX * 0.025;
			position.z += deltaZ * 0.025;
		}
	}
	void StartMoveXY(int x, int y) {
		startX = x;
		startY = y;
		movingXY = 1;
	}
	void StopMoveXY() {
		startX = 0;
		startY = 0;
		movingXY = 0;
	}
	void UpdatePositionXY(int deltaX, int deltaY) {
		if (movingXY) {
			position.x += deltaX * 0.0025;
			position.y += deltaY * 0.0025;
		}
	}

	Message::State OnMessage(Message mes);

	RayVector GetVectorRay(int x, int y);

	D3DXMATRIX GetTransformMatrix() {
		D3DXMATRIX rotX, rotY, rotZ, pos;
		D3DXMATRIX finalm;

		D3DXMatrixRotationX(&rotX, D3DXToRadian(rotation.x));
		D3DXMatrixRotationY(&rotY, D3DXToRadian(rotation.y));
		D3DXMatrixRotationZ(&rotZ, D3DXToRadian(rotation.z));
		D3DXMatrixTranslation(&pos, position.x, position.y, position.z);

		finalm = rotX * rotY * rotZ * pos;
		D3DXMatrixInverse(&finalm, 0, &finalm);
		return  finalm;
	}

private:
	void getPlanePoints(float dist, D3DXVECTOR3 *pts);
	D3DXMATRIX makeOrientationMatrix();

	int oldX = 0;
	int oldY = 0;
};

#endif /* SOURCE_CAMERA_H_ */

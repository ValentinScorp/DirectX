#include "Precompiled.h"

Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	position = pos;
	rotation = rot;
	fovy = 45;
	nearPlane = 1;
	farPlane = 200;
}


Camera::~Camera()
{
}

Message::State Camera::OnMessage(Message mes)
{
	if (mes.type == "user_input")
	{
		if (mes.name == "right_mouse_button_down") {
			oldX = mes.x;
			oldY = mes.y;
			movingXY  = 1;
		}
		if (mes.name == "right_mouse_button_up") {
			movingXY = 0;
		}
		if (mes.name == "mouse_wheel") {
			if (mes.delta > 0) {
				moveUp(1);
			}
			if (mes.delta < 0) {
				moveDown(2);
			}
		}
		if (mes.name == "mouse_move") {
			if (movingXY) {
				position.x += ((mes.x - oldX) * 0.025);
				position.y += ((mes.y - oldY) * 0.025);
				oldX = mes.x;
				oldY = mes.y;
			}
		}
	}
}

RayVector Camera::GetVectorRay(int x, int y)
{
	D3DXVECTOR3 pts[4];
	getPlanePoints(farPlane, pts);
	float dx = (float)x / (float)SCREEN_WIDTH;
	float dz = (float)y / (float)SCREEN_HEIGHT;
	D3DXVECTOR3 vdx = pts[1] - pts[0];
	D3DXVECTOR3 vdz = pts[3] - pts[0];
	D3DXVECTOR3 end = pts[0] + (vdx * dx) + (vdz * dz);
	D3DXMATRIX orientation = makeOrientationMatrix();

	D3DXVec3TransformCoord(&end, &end, &orientation);

	return RayVector(position, end);
}

void Camera::getPlanePoints(float dist, D3DXVECTOR3 *pts)
{
	float aspect = ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

	float fov = D3DXToRadian(fovy);

	float y = dist * float(tan(fov * 0.5));
	float x = y * aspect;

	pts[0].x = -x;  pts[0].y = y;	pts[0].z = dist;
	pts[1].x = x;   pts[1].y = y;	pts[1].z = dist;
	pts[2].x = x;   pts[2].y = -y; 	pts[2].z = dist;
	pts[3].x = -x;  pts[3].y = -y; 	pts[3].z = dist;

	/*
	pts[0].x = -x;  pts[0].y = y;	pts[0].z = dist;
	pts[1].x = x;   pts[1].y = y;	pts[1].z = dist;
	pts[2].x = x;   pts[2].y = -y; 	pts[2].z = dist;
	pts[3].x = -x;  pts[3].y = -y; 	pts[3].z = dist;
	*/
}

D3DXMATRIX Camera::makeOrientationMatrix()
{
	D3DXVECTOR3 cam_pos = position;
	D3DXVECTOR3 cam_rot = rotation;

	D3DXMATRIX mat_rot_x, mat_rot_y, mat_rot_z, mat_trans;
	D3DXMatrixTranslation(&mat_trans, cam_pos.x, cam_pos.y, cam_pos.z);
	D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(cam_rot.x));
	D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(cam_rot.y));
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(cam_rot.z));

	D3DXMATRIX orientation = mat_rot_x * mat_rot_y * mat_rot_z * mat_trans;

	return orientation;
}

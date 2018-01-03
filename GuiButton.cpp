#include "Precompiled.h"

GuiButton::GuiButton(IDirect3DDevice9* pDevice, D3DXVECTOR2 pos, std::string bitmapFileName, int id)
{
    position = pos;
    this->id = id;
    dimension.x = 32;
    dimension.y = 32;
    bitmap = new GuiBitmap;
	bitmap->Init(pDevice, bitmapFileName);
	bitmap->SetPosition(position);

	D3DXCreateTextureFromFile(pDevice, "button_frame.png", &frameTexture);
	D3DXCreateSprite(pDevice, &sprite);
}

GuiButton::~GuiButton()
{
    Destroy();
}

void GuiButton::OnMessage(Message mes)
{
    if (mes.type == "user_input" && mes.name == "left_mouse_button_down") {
        state = BS_PRESS;
	}
	if (mes.type == "user_input" && mes.name == "left_mouse_button_up") {
        state = BS_UP;
	}
}

void GuiButton::Init()
{

}

void GuiButton::Draw()
{
    bitmap->Draw();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    float degree = 0;
    if (state == BS_PRESS) {
        degree = 180;
    }
    D3DXMATRIX rotationMatrix;
    D3DXVECTOR2 rotation_center(dimension.x / 2, dimension.y / 2);
    D3DXVECTOR2 frame_position(position.x, position.y);
    D3DXMatrixTransformation2D(&rotationMatrix, NULL, 0, NULL, &rotation_center, D3DXToRadian(degree), &frame_position);
    sprite->SetTransform(&rotationMatrix);
    sprite->Draw(frameTexture, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
    D3DXMatrixRotationZ(&rotationMatrix, 0);
    sprite->SetTransform(&rotationMatrix);
    sprite->End();
}

void GuiButton::Destroy()
{
    if (bitmap != nullptr){
        delete bitmap;
        bitmap = nullptr;
    }
    if (sprite != nullptr) {
		sprite->Release();
		sprite = nullptr;
	}
}

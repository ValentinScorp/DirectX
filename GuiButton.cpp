#include "Precompiled.h"

GuiButton::GuiButton(IDirect3DDevice9* pDevice, D3DXVECTOR2 pos, std::string bitmapFileName, int id)
{
    if (bitmapFileName == "") {
        bitmapFileName = "button_background.png";
    }
    position = pos;
    this->id = id;
    dimension.x = 32;
    dimension.y = 32;
    bitmap = new GuiBitmap(pDevice, bitmapFileName);
	bitmap->SetPosition(position);

	D3DXCreateTextureFromFile(pDevice, "button_frame.png", &frameTexture);
	D3DXCreateSprite(pDevice, &sprite);

	text = new GuiText(pDevice, "");
    text->SetPosition(position);
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

void GuiButton::Draw()
{
    bitmap->setWidth(dimension.x);
    bitmap->Draw();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);

    float degree = 0;
    if (state == BS_PRESS) {
        degree = 180;
    }

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR2 spriteCentre = D3DXVECTOR2(dimension.x / 2.0f, dimension.y / 2.0f);
    D3DXMATRIX mat;
    D3DXVECTOR2 scaling(dimension.x / 32.0f, dimension.y / 32.0f);
    D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, D3DXToRadian(degree), &position);

    sprite->SetTransform(&mat);
    sprite->Draw(frameTexture, NULL, NULL, NULL, 0xFFFFFFFF);
    sprite->End();

    D3DXVECTOR2 newPosition = position;
    newPosition.x += 4 * (dimension.x / 32.0f);
    newPosition.y += 4 * (dimension.y / 32.0f);
    text->SetPosition(newPosition);
    text->Draw();
}

void GuiButton::Destroy()
{
    if (bitmap != nullptr){
        delete bitmap;
        bitmap = nullptr;
    }
    if (text != nullptr){
        delete text;
        text = nullptr;
    }
    if (sprite != nullptr) {
		sprite->Release();
		sprite = nullptr;
	}
}

void GuiButton::setText(std::string newText)
{
    text->setText(newText);
}

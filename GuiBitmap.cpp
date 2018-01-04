/*
 * GuiBitmap.cpp
 *
 *  Created on: 28 лист. 2017 р.
 *      Author: Valentin
 */

#include "Precompiled.h"

GuiBitmap::GuiBitmap(IDirect3DDevice9* dev, std::string fname) {
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	dimension.x = 32;
    dimension.y = 32;

	D3DXCreateTextureFromFile(dev, fname.c_str(), &texture);
	D3DXCreateSprite(dev, &sprite);
}

GuiBitmap::~GuiBitmap() {
	Destroy();
}

void GuiBitmap::Draw() {

    float degree = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR2 spriteCentre = D3DXVECTOR2(dimension.x / 2.0f, dimension.y / 2.0f);
    D3DXMATRIX mat;
    D3DXVECTOR2 scaling(1.0f, 1.0f);
    D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, D3DXToRadian(degree), &position);

    sprite->SetTransform(&mat);
    RECT rect = {(LONG)0, (LONG)0, (LONG)dimension.x, (LONG)dimension.y};
    sprite->Draw(texture, &rect, NULL, NULL, color);
    sprite->End();
}

void GuiBitmap::Destroy() {
    if (sprite != nullptr) {
		sprite->Release();
		sprite = nullptr;
	}
	if (texture != nullptr) {
		texture->Release();
		texture = nullptr;
	}
}

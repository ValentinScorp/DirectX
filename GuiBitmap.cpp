/*
 * GuiBitmap.cpp
 *
 *  Created on: 28 лист. 2017 р.
 *      Author: Valentin
 */

#include "Precompiled.h"

GuiBitmap::GuiBitmap() {
	position.x = 0;
	position.y = 0;
	position.z = 0;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

GuiBitmap::~GuiBitmap() {
	if (sprite) {
		sprite->Release();
	}
	if (texture) {
		texture->Release();
	}
}

void GuiBitmap::Init(IDirect3DDevice9* dev, std::string fname) {
	D3DXCreateTextureFromFile(dev, fname.c_str(), &texture);
	D3DXCreateSprite(dev, &sprite);
}

void GuiBitmap::Draw() {
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rect = {0, 0, 32, 32};
	sprite->Draw(texture, &rect, NULL, &position, color);
	sprite->End();
}

void GuiBitmap::SetPosition(D3DXVECTOR2 pos) {
	position.x = pos.x;
	position.y = pos.y;
	position.z = 0;
}

#include "Precompiled.h"

GuiList::GuiList(IDirect3DDevice9* dev, D3DXVECTOR2 pos, int id)
{
    position = pos;
    this->id = id;
    this->pDevice = dev;
    dimension.x = 100;
    dimension.y = 24;
}

GuiList::~GuiList()
{
}

void GuiList::Draw()
{
    for (GuiText *item : items) {
        if (item != nullptr) {
            item->Draw();
        }
    }
}

void GuiList::Destroy()
{
    for (GuiText *item : items) {
        if (item != nullptr) {
            delete item;
        }
    }
    items.clear();
}

void GuiList::addItem(std::string text)
{
    GuiText *netItem = new GuiText(pDevice, text);
    D3DXVECTOR2 newPos = position;
    newPos.y += (items.size() * 24);
    dimension.y += 24;
    netItem->SetPosition(newPos);
    items.push_back(netItem);
}

void GuiList::OnMessage(Message mes)
{
    if (mes.type == "user_input" && mes.name == "left_mouse_button_down") {
        std::cout << "list" << std::endl;
	}
	if (mes.type == "user_input" && mes.name == "left_mouse_button_up") {

	}
}

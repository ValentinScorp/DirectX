#include "Precompiled.h"

GuiSystem::GuiSystem(IDirect3DDevice9* dev)
{
    if (dev == nullptr) {
        throw std::invalid_argument("GuiSystem creation error");
    }
    pDevice = dev;
}

GuiSystem::~GuiSystem()
{

}
Message::State GuiSystem::OnMessage(Message mes)
{
    Message::State messageState = Message::MS_NOT_HANDLED;

    if (mes.type == "user_input" && mes.name == "mouse_move") {
	}
	if (mes.type == "user_input" && mes.name == "left_mouse_button_down") {
        for (GuiComponent* gc : components) {
            if (gc->IsInBorders(D3DXVECTOR2(mes.x, mes.y))){
                gc->OnMessage(mes);
                this->SendMessage(Message("gui_message", "change_brush_texture", mes.x, mes.y, gc->GetId()));
                messageState = Message::MS_HANDLED;
            }
        }
	}
	if (mes.type == "user_input" && mes.name == "left_mouse_button_up") {
        for (GuiComponent* gc : components) {
            gc->OnMessage(mes);
        }
	}
	return messageState;
}

void GuiSystem::CreateButton(D3DXVECTOR2 position, std::string bitmapFileName, int id)
{
    GuiComponent *guibutton = new GuiButton(pDevice, position, bitmapFileName, id);
    components.push_back(guibutton);
}

void GuiSystem::Draw()
{
    for (GuiComponent* gc : components) {
        if (gc != nullptr) {
            gc->Draw();
        }
    }
}

void GuiSystem::Destroy()
{
    for (GuiComponent* gc : components) {
        if (gc != nullptr) {
            delete gc;
        }
    }
    components.clear();
}

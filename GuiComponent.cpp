#include "Precompiled.h"

GuiComponent::GuiComponent()
{
    position.x = 0;
    position.y = 0;
}

GuiComponent::~GuiComponent()
{

}

bool GuiComponent::IsInBorders(D3DXVECTOR2 point)
{
    point = point - position;
    if (point.x > dimension.x || point.x < 0) {
        return 0;
    }
    if (point.y > dimension.y || point.y < 0) {
        return 0;
    }
    return 1;
}

void GuiComponent::SetPosition(D3DXVECTOR2 newPos)
{
    position = newPos;
}

void GuiComponent::setWidth(float width) {
    dimension.x = width;
}

int GuiComponent::GetId()
{
    return id;
}

#include "Precompiled.h"


UserInput::UserInput()
{
}

UserInput::~UserInput()
{
}
void UserInput::RegisterGuiReceiver(MessageReceiver *mr)
{
    guiSystem = mr;
}
void UserInput::SendMessage(Message mes)
{
    if (guiSystem->OnMessage(mes) == Message::MS_NOT_HANDLED) {
        MessageSender::SendMessage(mes);
    }
}

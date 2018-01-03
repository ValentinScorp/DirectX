#ifndef GUISYSTEM_H
#define GUISYSTEM_H

class GuiSystem : public MessageReceiver, public MessageSender
{
    private:
        IDirect3DDevice9* pDevice = nullptr;
        std::list<GuiComponent*> components;

    public:
        GuiSystem(IDirect3DDevice9* dev);
        virtual ~GuiSystem();

        void CreateButton(D3DXVECTOR2 position, std::string bitmapFileName, int id);
        void Draw();

        Message::State OnMessage(Message mes);

        void Destroy();

    private:
};

#endif // GUISYSTEM_H

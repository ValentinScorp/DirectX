#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

class GuiComponent
{
    protected:
        D3DXVECTOR2 position;
        D3DXVECTOR2 dimension;

        int id = 0;

    public:
        GuiComponent();
        virtual ~GuiComponent();

        virtual void Init() = 0;
        virtual void Draw() = 0;
        virtual void Destroy() = 0;
        virtual void OnMessage(Message mes) = 0;

        int GetId();

        bool IsInBorders(D3DXVECTOR2 point);
};

#endif // GUICOMPONENT_H

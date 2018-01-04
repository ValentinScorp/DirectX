#ifndef GUIBUTTON_H
#define GUIBUTTON_H

class GuiButton : public GuiComponent
{
    private:
        GuiComponent *bitmap = nullptr;
        GuiText *text = nullptr;
        IDirect3DTexture9 *frameTexture = nullptr;
        ID3DXSprite *sprite = nullptr;

        enum ButtonState {
            BS_UP,
            BS_OVER,
            BS_PRESS
        };

        ButtonState state = BS_UP;

    public:
        GuiButton(IDirect3DDevice9* dev, D3DXVECTOR2 pos, std::string bitmapFileName, int id);
        virtual ~GuiButton();

        void OnMessage(Message mes);

        virtual void Draw();
        virtual void Destroy();

        void setText(std::string newText);
};

#endif // GUIBUTTON_H

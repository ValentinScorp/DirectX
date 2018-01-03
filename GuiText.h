#ifndef GUITEXT_H
#define GUITEXT_H


class GuiText : public GuiComponent
{
    private:
        std::string text;
    	ID3DXFont*	font = nullptr;
    public:
        GuiText(std::string text);
        virtual ~GuiText();

        void Init(IDirect3DDevice9* pDevice);
        void Draw();
        void Destroy();
};

#endif // GUITEXT_H

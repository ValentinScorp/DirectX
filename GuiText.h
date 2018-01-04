#ifndef GUITEXT_H
#define GUITEXT_H


class GuiText : public GuiComponent
{
    private:
        std::string text;
    	ID3DXFont*	font = nullptr;
    public:
        GuiText(IDirect3DDevice9* pDevice, std::string text);
        virtual ~GuiText();

        void Draw();
        void Destroy();

        void setText(std::string newText);
};

#endif // GUITEXT_H

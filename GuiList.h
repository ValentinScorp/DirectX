#ifndef GUILIST_H
#define GUILIST_H


class GuiList : public GuiComponent
{
private:
    std::vector<GuiText*> items;
    IDirect3DDevice9* pDevice = nullptr;

public:
    GuiList(IDirect3DDevice9* dev, D3DXVECTOR2 pos, int id);
    virtual ~GuiList();

    void addItem(std::string text);
    virtual void Draw();
    virtual void Destroy();

    void OnMessage(Message mes);

};

#endif // GUILIST_H

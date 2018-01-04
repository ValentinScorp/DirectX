#ifndef SOURCE_GUIBITMAP_H_
#define SOURCE_GUIBITMAP_H_

class GuiBitmap : public GuiComponent {
public:
	GuiBitmap(IDirect3DDevice9* dev, std::string fname);
	~GuiBitmap();

	void Draw();

	void Destroy();
private:

	IDirect3DTexture9 *texture = nullptr;
	ID3DXSprite *sprite = nullptr;

	D3DCOLOR color;
};

#endif /* SOURCE_GUIBITMAP_H_ */

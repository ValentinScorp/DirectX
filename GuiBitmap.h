#ifndef SOURCE_GUIBITMAP_H_
#define SOURCE_GUIBITMAP_H_

class GuiBitmap {
public:
	GuiBitmap();
	~GuiBitmap();

	void Init(IDirect3DDevice9* dev, std::string fname);
	void Draw();

	void SetPosition(D3DXVECTOR2 pos);
private:

	IDirect3DTexture9 *texture = nullptr;
	//IDirect3DTexture9 *frameTexture = nullptr;
	ID3DXSprite *sprite = nullptr;

	D3DXVECTOR3 position;
	D3DCOLOR color;
};

#endif /* SOURCE_GUIBITMAP_H_ */

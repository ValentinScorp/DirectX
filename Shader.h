#ifndef SOURCE_SHADER_H_
#define SOURCE_SHADER_H_

#include "Precompiled.h"

class Shader {
public:
	Shader();
	virtual ~Shader();

	void CreateVertexShader(IDirect3DDevice9* dev, std::string fname, std::string entrypoint);
	void CreatePixelShader(IDirect3DDevice9* dev, std::string fname, std::string entrypoint);

	void PrepareTexture(std::string name);
	void PrepareTextureArray(std::string name);
	void PrepareMatrix(std::string name);

	void Activate();
	void SetTexture(IDirect3DTexture9* tex);
	void SetArrayTexture(std::vector<IDirect3DTexture9*> *textures);
	void SetMatrix(D3DXMATRIX *mat);

	void Destroy();

private:
	void compileShader(std::string fname, std::string entrypoint, std::string shaderver);


	IDirect3DDevice9* device = 0;

	ID3DXBuffer* compiledShader = 0;
	ID3DXConstantTable* constantTable = 0;
	IDirect3DVertexShader9* vertexShader = 0;
	IDirect3DPixelShader9* pixelShader = 0;

	std::vector<D3DXCONSTANT_DESC> texturesDescription;
	D3DXCONSTANT_DESC textureDescription;
	D3DXHANDLE matrixHandle = 0;
};

#endif /* SOURCE_SHADER_H_ */

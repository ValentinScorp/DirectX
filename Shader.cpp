#include "Shader.h"

Shader::Shader() {
}

Shader::~Shader() {
}

void Shader::CreateVertexShader(IDirect3DDevice9* dev, std::string fname, std::string entrypoint) {
	device = dev;
	compileShader(fname, entrypoint, "vs_3_0");
	device->CreateVertexShader ((DWORD*)compiledShader->GetBufferPointer(), &vertexShader);
}

void Shader::CreatePixelShader(IDirect3DDevice9* dev, std::string fname, std::string entrypoint) {
	device = dev;
	compileShader(fname, entrypoint, "ps_3_0");
	device->CreatePixelShader ((DWORD*)compiledShader->GetBufferPointer(), &pixelShader);
}

void Shader::PrepareTextureArray(std::string name) {
	UINT count = 1;

	D3DXHANDLE texSamplers = constantTable->GetConstantByName(0, name.c_str());
	D3DXCONSTANT_DESC texSamplersDesc;
	constantTable->GetConstantDesc(texSamplers, &texSamplersDesc, &count);

	D3DXHANDLE texSampler;
	for (UINT i = 0; i < texSamplersDesc.Elements; i++) {
		texSampler = constantTable->GetConstantElement(texSamplers, i);
		D3DXCONSTANT_DESC texConstantDesc;
		constantTable->GetConstantDesc(texSampler, &texConstantDesc, &count);
		texturesDescription.push_back(texConstantDesc);
	}
}

void Shader::PrepareMatrix(std::string name) {
	matrixHandle = constantTable->GetConstantByName(0, name.c_str());
}

void Shader::PrepareTexture(std::string name) {
	UINT count = 1;
	D3DXHANDLE texSampler = constantTable->GetConstantByName(0, name.c_str());
	constantTable->GetConstantDesc(texSampler, &textureDescription, &count);
}

void Shader::Destroy() {
	if (vertexShader) {
		vertexShader->Release();
		vertexShader = nullptr;
	}
	if (pixelShader) {
		pixelShader->Release();
		pixelShader = nullptr;
	}
	if (compiledShader) {
		compiledShader->Release();
		compiledShader = nullptr;
	}

}

void Shader::Activate() {
	if (device == 0) {
		return;
	}
	if (vertexShader != 0) {
		device->SetVertexShader(vertexShader);
	}
	if (pixelShader != 0) {
		device->SetPixelShader(pixelShader);
	}
}

void Shader::SetTexture(IDirect3DTexture9* tex) {
	device->SetTexture(textureDescription.RegisterIndex, tex);
	device->SetSamplerState(textureDescription.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(textureDescription.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(textureDescription.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(textureDescription.RegisterIndex, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	device->SetSamplerState(textureDescription.RegisterIndex, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
}

void Shader::SetArrayTexture(std::vector<IDirect3DTexture9*> *textures) {
	if ((*textures).size() != texturesDescription.size()) {
		return;
	}
	for (size_t i = 0; i < (*textures).size(); i++) {
		device->SetTexture(texturesDescription[i].RegisterIndex, (*textures)[i]);
		device->SetSamplerState(texturesDescription[i].RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(texturesDescription[i].RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(texturesDescription[i].RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(texturesDescription[i].RegisterIndex, D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
		device->SetSamplerState(texturesDescription[i].RegisterIndex, D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
	}
}

void Shader::SetMatrix(D3DXMATRIX *mat) {
	constantTable->SetMatrix(device, matrixHandle, mat);
}

void Shader::compileShader(std::string fname, std::string entrypoint, std::string shaderver) {
	ID3DXBuffer* errorBuffer = 0;

	D3DXCompileShaderFromFile(fname.c_str(), 0, 0, entrypoint.c_str(), shaderver.c_str(),
								D3DXSHADER_DEBUG, &compiledShader, &errorBuffer, &constantTable);

	if( errorBuffer != NULL ) {
		std::cout << "Shader compile error ========>" << std::endl;
		std::cout << (char*)errorBuffer->GetBufferPointer() << std::endl;
		errorBuffer->Release();
	}
}

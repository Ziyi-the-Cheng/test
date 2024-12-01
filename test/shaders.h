#pragma once
#include "device.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <map>
#include "ma.h"
#include "ShaderReflection.h"
#pragma comment(lib, "dxguid.lib")
class shader {
public:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	std::vector<ConstantBuffer> psConstantBuffers;
	std::vector<ConstantBuffer> vsConstantBuffers;
	std::map<std::string, int> textureBindPointsVS;
	std::map<std::string, int> textureBindPointsPS;
	float time = 0.f;
	Vec4 lights[4];

	std::string readFile(std::string file) {
		std::stringstream buffer;
		std::ifstream vs(file);
		buffer << vs.rdbuf();
		vs.close();
		return buffer.str();
	}

	void create(device &dd, std::string vs_file, std::string ps_file) {
		std::string vsf = readFile(vs_file);
		std::string psf = readFile(ps_file);
		loadVS(dd, vsf);
		loadPS(dd, psf);
	}

	void loadVS(device &dd, std::string hlsl) {
		ID3DBlob* shader;
		ID3DBlob* status;
		HRESULT hr = D3DCompile(hlsl.c_str(), strlen(hlsl.c_str()), NULL, NULL, NULL, "VS", "vs_5_0", 0, 0, &shader, &status);
		if (FAILED(hr)) {
			(char*)status->GetBufferPointer();
			exit(0);
		}
		dd.device->CreateVertexShader(shader->GetBufferPointer(), shader->GetBufferSize(), NULL, &vertexShader);
		
		D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
		{
			{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		dd.device->CreateInputLayout(layoutDesc, 4, shader->GetBufferPointer(), shader->GetBufferSize(), &layout);

		ConstantBufferReflection reflection;
		reflection.build(dd, shader, vsConstantBuffers, textureBindPointsVS, ShaderStage::VertexShader);
	}

	void loadPS(device& core, std::string hlsl)
	{
		ID3DBlob* shader;
		ID3DBlob* status;
		HRESULT hr = D3DCompile(hlsl.c_str(), strlen(hlsl.c_str()), NULL, NULL, NULL, "PS", "ps_5_0", 0, 0, &shader, &status);
		if (FAILED(hr))
		{
			printf("%s\n", (char*)status->GetBufferPointer());
			exit(0);
		}
		core.device->CreatePixelShader(shader->GetBufferPointer(), shader->GetBufferSize(), NULL, &pixelShader);
		ConstantBufferReflection reflection;
		reflection.build(core, shader, psConstantBuffers, textureBindPointsPS, ShaderStage::PixelShader);
	}

	void updateConstant(std::string constantBufferName, std::string variableName, void* data, std::vector<ConstantBuffer>& buffers)
	{
		for (int i = 0; i < buffers.size(); i++)
		{
			if (buffers[i].name == constantBufferName)
			{
				buffers[i].update(variableName, data);
				return;
			}
		}
	}
	void updateConstantVS(std::string constantBufferName, std::string variableName, void* data)
	{
		updateConstant(constantBufferName, variableName, data, vsConstantBuffers);
	}
	void updateConstantPS(std::string constantBufferName, std::string variableName, void* data)
	{
		updateConstant(constantBufferName, variableName, data, psConstantBuffers);
	}

	void apply(device &dd) {
		
		for (int i = 0; i < vsConstantBuffers.size(); i++)
		{
			vsConstantBuffers[i].upload(dd);
		}
		for (int i = 0; i < psConstantBuffers.size(); i++)
		{
			psConstantBuffers[i].upload(dd);
		}
		dd.devicecontext->IASetInputLayout(layout);
		dd.devicecontext->VSSetShader(vertexShader, NULL, 0);
		dd.devicecontext->PSSetShader(pixelShader, NULL, 0);

	}
};
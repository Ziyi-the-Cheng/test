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

	/*void shine(device& dd) {
		ConstantBuffer cb;
		cb.init(dd, 16, 0, PixelShader);
		psConstantBuffers.push_back(cb);
		psConstantBuffers[0].update("nn", NULL);
		psConstantBuffers[0].upload(dd);
	}*/

	void create(device &dd, std::string vs_file, std::string ps_file) {
		std::string vsf = readFile(vs_file);
		std::string psf = readFile(ps_file);
		std::cout << vsf;
		compileVS(dd, vsf);
		loadPS(dd, psf);
	}

	void compileVS(device &dd, std::string hlsl) {
		ID3DBlob* compiledVertexShader;
		ID3DBlob* status;
		HRESULT hr = D3DCompile(hlsl.c_str(), strlen(hlsl.c_str()), NULL, NULL, NULL, "VS", "vs_5_0", 0, 0, &compiledVertexShader, &status);
		if (FAILED(hr)) {
			(char*)status->GetBufferPointer();
			exit(0);
		}
		dd.device->CreateVertexShader(compiledVertexShader->GetBufferPointer(), compiledVertexShader->GetBufferSize(), NULL, &vertexShader);
		
		
		D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
		{
			{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		dd.device->CreateInputLayout(layoutDesc, 2, compiledVertexShader->GetBufferPointer(), compiledVertexShader->GetBufferSize(), &layout);
	}

	void compilePS(device& dd, std::string hlsl) {
		ID3DBlob* compiledPixelShader;
		ID3DBlob* status;
		HRESULT hr = D3DCompile(hlsl.c_str(), strlen(hlsl.c_str()), NULL, NULL, NULL, "PS", "ps_5_0", 0, 0, &compiledPixelShader, &status);
		if (FAILED(hr)) {
			(char*)status->GetBufferPointer();
			exit(0);
		}
		dd.device->CreatePixelShader(compiledPixelShader->GetBufferPointer(), compiledPixelShader->GetBufferSize(), NULL, &pixelShader);
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

		/*for (auto& cb : psConstantBuffers) {
			if (cb.name == "nn") {
				float time = 0.f;

				cb.update("time", &time);
				cb.upload(core);
			}
		}*/
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
		time += 0.005f;

		for (int i = 0; i < 4; i++)
		{
			float angle = time + (i * 3.141592f / 2.0f);
			lights[i] = Vec4(1024 / 2.0f + (cosf(angle) * (1024 * 0.3f)),
				1024 / 2.0f + (sinf(angle) * (1024 * 0.3f)),
				0, 0);
		}


		updateConstantPS("ll", "time", &time);
		updateConstantPS("ll", "lights", &lights);
		for (int i = 0; i < psConstantBuffers.size(); i++)
		{
			psConstantBuffers[i].upload(dd);
		}
		dd.devicecontext->IASetInputLayout(layout);
		dd.devicecontext->VSSetShader(vertexShader, NULL, 0);
		dd.devicecontext->PSSetShader(pixelShader, NULL, 0);

	}
};
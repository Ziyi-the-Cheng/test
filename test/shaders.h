#pragma once
#include "device.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <map>
#pragma comment(lib, "dxguid.lib")
class shader {
public:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;


	std::string readFile(std::string file) {
		std::stringstream buffer;
		std::ifstream vs(file);
		buffer << vs.rdbuf();
		vs.close();
		return buffer.str();
	}

	void create(device &dd, std::string vs_file, std::string ps_file) {
		std::string vsf = readFile("vs.txt");
		std::string psf = readFile("ps.txt");
		std::cout << vsf;
		compileVS(dd, vsf);
		compilePS(dd, psf);
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

	void apply(device &dd) {
		dd.devicecontext->IASetInputLayout(layout);
		dd.devicecontext->VSSetShader(vertexShader, NULL, 0);
		dd.devicecontext->PSSetShader(pixelShader, NULL, 0);

	}
};
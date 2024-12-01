#pragma once
#include "device.h"
#include "ma.h"
#include "shaders.h"

struct STATIC_VERTEX
{
	Vec3 pos;
	Vec3 normal;
	Vec3 tangent;
	float tu;
	float tv;
};

class Mash {
public:
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	int indicesSize;
	UINT strides;

	void init(void* vertices, int vertexSizeInBytes, int numVertices, unsigned int* indices, int numIndices, device& device) {
		D3D11_BUFFER_DESC bd;
		memset(&bd, 0, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * numIndices;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = indices;
		device.device->CreateBuffer(&bd, &data, &indexBuffer);
		bd.ByteWidth = vertexSizeInBytes * numVertices;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		data.pSysMem = vertices;
		device.device->CreateBuffer(&bd, &data, &vertexBuffer);
		indicesSize = numIndices;
		strides = vertexSizeInBytes;
	}

	void init(std::vector<STATIC_VERTEX> vertices, std::vector<unsigned int> indices, device& device)
	{
		init(&vertices[0], sizeof(STATIC_VERTEX), vertices.size(), &indices[0], indices.size(), device);
	}

	void draw(device& devicecontext) {
		UINT offsets = 0;
		devicecontext.devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		devicecontext.devicecontext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offsets);
		devicecontext.devicecontext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		devicecontext.devicecontext->DrawIndexed(indicesSize, 0, 0);
	}
};

class Plane {
public:
	Mash geometry;
	Matrix planeWorld;
	Matrix vp;
	float t = 0.0f;
	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		//Frame frame;
		//frame.fromVector(n);
		//v.tangent = frame.u;
		v.tangent = Vec3(0, 0, 0);
		v.tu = tu;
		v.tv = tv;
		return v;
	}

	void init(device& core) {
		std::vector<STATIC_VERTEX> vertices;
		vertices.push_back(addVertex(Vec3(-1.5, 0, -1.5), Vec3(0, 1, 0), 0, 0));
		vertices.push_back(addVertex(Vec3(1.5, 0, -1.5), Vec3(0, 1, 0), 1, 0));
		vertices.push_back(addVertex(Vec3(-1.5, 0, 1.5), Vec3(0, 1, 0), 0, 1));
		vertices.push_back(addVertex(Vec3(1.5, 0, 1.5), Vec3(0, 1, 0), 1, 1));
		std::vector<unsigned int> indices;
		indices.push_back(2); indices.push_back(1); indices.push_back(0);
		indices.push_back(1); indices.push_back(2); indices.push_back(3);
		geometry.init(vertices, indices, core);
	}

	void draw(shader* shader, device& core) {
		t += 0.005f;
		Vec3 from = Vec3(11 * cos(t), 5, 11 * sin(t));
		Vec3 to = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
		shader->updateConstantVS("staticMeshBuffer", "W", &planeWorld);
		shader->updateConstantVS("staticMeshBuffer", "VP", &vp);
		geometry.draw(core);
	}
};
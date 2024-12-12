#pragma once
#include "device.h"
#include "ma.h"
#include "shaders.h"
#include"GEMLoader.h"
#include "texture.h"
#include "Camera.h"

struct STATIC_VERTEX
{
	Vec3 pos;
	Vec3 normal;
	Vec3 tangent;
	float tu;
	float tv;
};

struct ANIMATED_VERTEX
{
	Vec3 pos;
	Vec3 normal;
	Vec3 tangent;
	float tu;
	float tv;
	unsigned int bonesIDs[4];
	float boneWeights[4];
};

class Mesh {
public:
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	int indicesSize;
	UINT strides;
	std::vector<std::string> textureFilenames;

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

	void init(std::vector<ANIMATED_VERTEX> vertices, std::vector<unsigned int> indices, device& device)
	{
		init(&vertices[0], sizeof(ANIMATED_VERTEX), vertices.size(), &indices[0], indices.size(), device);
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
	Mesh geometry;
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
		vertices.push_back(addVertex(Vec3(-15, 0, -15), Vec3(0, 1, 0), 0, 0));
		vertices.push_back(addVertex(Vec3(15, 0, -15), Vec3(0, 1, 0), 1, 0));
		vertices.push_back(addVertex(Vec3(-15, 0, 15), Vec3(0, 1, 0), 0, 1));
		vertices.push_back(addVertex(Vec3(15, 0, 15), Vec3(0, 1, 0), 1, 1));
		std::vector<unsigned int> indices;
		indices.push_back(2); indices.push_back(1); indices.push_back(0);
		indices.push_back(1); indices.push_back(2); indices.push_back(3);
		geometry.init(vertices, indices, core);
	}

	void draw(shader* shader, device& core, Camera& cam) {
		shader->updateConstantVS("staticMeshBuffer", "W", &cam.planeWorld);
		shader->updateConstantVS("staticMeshBuffer", "VP", &cam.vp);
		shader->apply(core);
		geometry.draw(core);
	}
};

class Cube {
public:
	Mesh geometry;
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
		Vec3 p0 = Vec3(-1.0f, -1.0f, -1.0f);
		Vec3 p1 = Vec3(1.0f, -1.0f, -1.0f);
		Vec3 p2 = Vec3(1.0f, 1.0f, -1.0f);
		Vec3 p3 = Vec3(-1.0f, 1.0f, -1.0f);
		Vec3 p4 = Vec3(-1.0f, -1.0f, 1.0f);
		Vec3 p5 = Vec3(1.0f, -1.0f, 1.0f);
		Vec3 p6 = Vec3(1.0f, 1.0f, 1.0f);
		Vec3 p7 = Vec3(-1.0f, 1.0f, 1.0f);

		vertices.push_back(addVertex(p0, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p1, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p2, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p3, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p5, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p4, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p7, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p6, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p4, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p0, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p3, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p7, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p1, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p5, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p6, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p2, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p3, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p2, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p6, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p7, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p4, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p5, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p1, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p0, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f));

		std::vector<unsigned int> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);
		indices.push_back(4); indices.push_back(5); indices.push_back(6);
		indices.push_back(4); indices.push_back(6); indices.push_back(7);
		indices.push_back(8); indices.push_back(9); indices.push_back(10);
		indices.push_back(8); indices.push_back(10); indices.push_back(11);
		indices.push_back(12); indices.push_back(13); indices.push_back(14);
		indices.push_back(12); indices.push_back(14); indices.push_back(15);
		indices.push_back(16); indices.push_back(17); indices.push_back(18);
		indices.push_back(16); indices.push_back(18); indices.push_back(19);
		indices.push_back(20); indices.push_back(21); indices.push_back(22);
		indices.push_back(20); indices.push_back(22); indices.push_back(23);

		geometry.init(vertices, indices, core);
	}

	void updateW(Matrix& m) {
		planeWorld = m;
	}

	void draw(shader* shader, device& core) {
		t += 0.0025f;
		Vec3 from = Vec3(11 * cos(t), 5, 11 * sin(t));
		Vec3 to = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
		shader->updateConstantVS("staticMeshBuffer", "W", &planeWorld);
		shader->updateConstantVS("staticMeshBuffer", "VP", &vp);
		shader->apply(core);
		geometry.draw(core);
	}

};

class Sphere {
public:
	Mesh geometry;
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

	void init(device& core, int rings, int segments, float radius) {
		std::vector<STATIC_VERTEX> vertices;
		std::vector<unsigned int> indices;

		for (int lat = 0; lat <= rings; lat++) {
			float theta = lat * 3.14159265f / rings;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);
			for (int lon = 0; lon <= segments; lon++) {
				float phi = lon * 2.0f * 3.14159265f / segments;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);
				Vec3 position(radius * sinTheta * cosPhi, radius * cosTheta, radius * sinTheta * sinPhi);
				Vec3 normal = position.normalize();
				float tu = 1.0f - (float)lon / segments;
				float tv = 1.0f - (float)lat / rings;
				vertices.push_back(addVertex(position, normal, tu, tv));
			}
		}

		for (int lat = 0; lat < rings; lat++)
		{
			for (int lon = 0; lon < segments; lon++)
			{
				int current = lat * (segments + 1) + lon;
				int next = current + segments + 1;
				indices.push_back(current);
				indices.push_back(next);
				indices.push_back(current + 1);
				indices.push_back(current + 1);
				indices.push_back(next);
				indices.push_back(next + 1);
			}
		}

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

class Tree {
public:
	std::vector<Mesh> meshes;
	Matrix planeWorld;
	Matrix vp;
	float t = 0.0f;

	void init(device& core) {
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		loader.load("acacia_003.gem", gemmeshes);
		for (int i = 0; i < gemmeshes.size(); i++) {
			Mesh mesh;
			std::vector<STATIC_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesStatic.size(); j++) {
				STATIC_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesStatic[j], sizeof(STATIC_VERTEX));
				vertices.push_back(v);
			}
			mesh.init(vertices, gemmeshes[i].indices, core);
			meshes.push_back(mesh);
		}
	}

	void updateW(Matrix& m) {
		planeWorld = m;
	}

	void draw(shader* shader, device& core) {
		t += 0.005f;
		Vec3 from = Vec3(11 * cos(t), 5, 11 * sin(t));
		Vec3 to = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
		shader->updateConstantVS("staticMeshBuffer", "W", &planeWorld);
		shader->updateConstantVS("staticMeshBuffer", "VP", &vp);
		shader->apply(core);
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i].draw(core);
		}
	}
};

class Pine {
public:
	std::vector<Mesh> meshes;
	Matrix planeWorld;
	Matrix vp;
	float t = 0.0f;
	std::vector<std::string> textureFilenames;

	void init(device& core, TextureManager& textures) {
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		loader.load("pine.gem", gemmeshes);
		for (int i = 0; i < gemmeshes.size(); i++) {
			std::vector<STATIC_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesStatic.size(); j++) {
				STATIC_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesStatic[j], sizeof(STATIC_VERTEX));
				vertices.push_back(v);
			}
			Mesh mesh;
			textureFilenames.push_back(gemmeshes[i].material.find("diffuse").getValue());
			textures.load(&core, gemmeshes[i].material.find("diffuse").getValue());
			mesh.init(vertices, gemmeshes[i].indices, core);
			meshes.push_back(mesh);
		}
	}

	void updateW(Matrix& m) {
		planeWorld = m;
	}

	void draw(shader* shader, device& core, TextureManager& textures) {
		t += 0.0025f;
		Vec3 from = Vec3(11 * cos(t), 5, 11 * sin(t));
		Vec3 to = Vec3(0.0f, 5.0f, 0.0f);
		Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
		shader->updateConstantVS("staticMeshBuffer", "W", &planeWorld);
		shader->updateConstantVS("staticMeshBuffer", "VP", &vp);
		shader->apply(core);
		for (int i = 0; i < meshes.size(); i++)
		{
			shader->bind("tex", core, textures.find(textureFilenames[i]));
			meshes[i].draw(core);
		}
	}
};

///////////////////////////////////

struct Bone
{
	std::string name;
	Matrix offset;
	int parentIndex;
};

struct Skeleton
{
	std::vector<Bone> bones;
	Matrix globalInverse;
};

struct AnimationFrame
{
	std::vector<Vec3> positions;
	std::vector<Quaternion> rotations;
	std::vector<Vec3> scales;
};

class AnimationSequence
{
public:
	std::vector<AnimationFrame> frames;
	float ticksPerSecond;

	Vec3 interpolate(Vec3 p1, Vec3 p2, float t) {
		return ((p1 * (1.0f - t)) + (p2 * t));
	}
	Quaternion interpolate(Quaternion q1, Quaternion q2, float t) {
		return Quaternion::slerp(q1, q2, t);
	}
	float duration() {
		return ((float)frames.size() / ticksPerSecond);
	}

	void calcFrame(float t, int& frame, float& interpolationFact)
	{
		interpolationFact = t * ticksPerSecond;
		frame = (int)floorf(interpolationFact);
		interpolationFact = interpolationFact - (float)frame;
		frame = min(frame, frames.size() - 1);
	}

	int nextFrame(int frame)
	{
		return min(frame + 1, frames.size() - 1);
	}

	Matrix interpolateBoneToGlobal(Matrix* matrices, int baseFrame, float interpolationFact, Skeleton* skeleton, int boneIndex) {
		int nextFrameIndex = nextFrame(baseFrame);
		Matrix scale = Matrix::scale(interpolate(frames[baseFrame].scales[boneIndex], frames[nextFrameIndex].scales[boneIndex], interpolationFact));
		Matrix rotation = interpolate(frames[baseFrame].rotations[boneIndex], frames[nextFrameIndex].rotations[boneIndex], interpolationFact).toMatrix();
		Matrix translation = Matrix::translation(interpolate(frames[baseFrame].positions[boneIndex], frames[nextFrameIndex].positions[boneIndex], interpolationFact));
		Matrix local = scale * rotation * translation;
		if (skeleton->bones[boneIndex].parentIndex > -1) {
			Matrix global = local * matrices[skeleton->bones[boneIndex].parentIndex];
			return global;
		}
		return local;
	}

};

class Animation
{
public:
	std::map<std::string, AnimationSequence> animations;
	Skeleton skeleton;
	void calcFrame(std::string name, float t, int& frame, float& interpolationFact) {
		animations[name].calcFrame(t, frame, interpolationFact);
	}
	Matrix interpolateBoneToGlobal(std::string name, Matrix* matrices, int baseFrame, float 						interpolationFact, int boneIndex) {
		return animations[name].interpolateBoneToGlobal(matrices, baseFrame, interpolationFact, &skeleton, boneIndex);
	}
	void calcFinalTransforms(Matrix* matrices)
	{
		for (int i = 0; i < bonesSize(); i++)
		{
			matrices[i] = skeleton.bones[i].offset * matrices[i] * skeleton.globalInverse;
		}
	}
	int bonesSize() {
		return skeleton.bones.size();
	}
};

class AnimationInstance
{
public:
	Animation* animation;
	std::string currentAnimation;
	float t;
	Matrix matrices[256];

	void resetAnimationTime()
	{
		t = 0;
	}
	bool animationFinished()
	{
		if (t > animation->animations[currentAnimation].duration())
		{
			return true;
		}
		return false;
	}

	void update(std::string name, float dt) {
		if (name == currentAnimation) {
			t += dt;
		}
		else {
			currentAnimation = name;  t = 0;
		}
		if (animationFinished() == true) { resetAnimationTime(); }
		int frame = 0;
		float interpolationFact = 0;
		animation->calcFrame(name, t, frame, interpolationFact);
		for (int i = 0; i < animation->bonesSize(); i++)
		{
			matrices[i] = animation->interpolateBoneToGlobal(name, matrices, frame, interpolationFact, i);
		}
		animation->calcFinalTransforms(matrices);
	}
};

class TRex {
public:
	std::vector<Mesh> meshes;
	Animation animation;
	AnimationInstance instance;
	std::vector<std::string> textureFilenames;
	Matrix planeWorld;
	Matrix vp;
	float t = 0.0f;
	float move;

	void init(device& core, std::string filename, TextureManager& textures) {
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		GEMLoader::GEMAnimation gemanimation;
		loader.load(filename, gemmeshes, gemanimation);
		for (int i = 0; i < gemmeshes.size(); i++) {
			Mesh mesh;
			std::vector<ANIMATED_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesAnimated.size(); j++) {
				ANIMATED_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesAnimated[j], sizeof(ANIMATED_VERTEX));
				vertices.push_back(v);
			}
			mesh.init(vertices, gemmeshes[i].indices,core);
			textureFilenames.push_back(gemmeshes[i].material.find("diffuse").getValue());
			textures.load(&core, gemmeshes[i].material.find("diffuse").getValue());
			meshes.push_back(mesh);
		}
		for (int i = 0; i < gemanimation.bones.size(); i++)
		{
			Bone bone;
			bone.name = gemanimation.bones[i].name;
			memcpy(&bone.offset, &gemanimation.bones[i].offset, 16 * sizeof(float));
			bone.parentIndex = gemanimation.bones[i].parentIndex;
			animation.skeleton.bones.push_back(bone);
		}
		for (int i = 0; i < gemanimation.animations.size(); i++)
		{
			std::string name = gemanimation.animations[i].name;
			AnimationSequence aseq;
			aseq.ticksPerSecond = gemanimation.animations[i].ticksPerSecond;
			for (int n = 0; n < gemanimation.animations[i].frames.size(); n++)
			{
				AnimationFrame frame;
				for (int index = 0; index < gemanimation.animations[i].frames[n].positions.size(); index++)
				{
					Vec3 p;
					Quaternion q;
					Vec3 s;
					memcpy(&p, &gemanimation.animations[i].frames[n].positions[index], sizeof(Vec3));
					frame.positions.push_back(p);
					memcpy(&q, &gemanimation.animations[i].frames[n].rotations[index], sizeof(Quaternion));
					frame.rotations.push_back(q);
					memcpy(&s, &gemanimation.animations[i].frames[n].scales[index], sizeof(Vec3));
					frame.scales.push_back(s);
				}
				aseq.frames.push_back(frame);
			}
			animation.animations.insert({ name, aseq });
		}
		instance.animation = &animation;
	}

	void updateW(Matrix& m) {
		planeWorld = m;
	}

	void moveRight() {
		move += 0.01f;
		planeWorld = planeWorld.translation(Vec3(0, 0, move));
	}

	void draw(shader* shader, device& core, TextureManager& textures, Camera& cam) {
		
		instance.update("Run", 0.001f);
		shader->updateConstantVS("animatedMeshBuffer", "W", &cam.planeWorld);
		shader->updateConstantVS("animatedMeshBuffer", "VP", &cam.vp);
		shader->updateConstantVS("animatedMeshBuffer", "bones", instance.matrices);
		shader->apply(core);
		for (int i = 0; i < meshes.size(); i++)
		{
			shader->bind("tex", core, textures.find(textureFilenames[i]));
			meshes[i].draw(core);
		}
	}
};

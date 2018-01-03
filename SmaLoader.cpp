#include "Precompiled.h"

#include <codecvt>

SmaLoader::SmaLoader()
{
}

GameObject* SmaLoader::load(std::string file)
{
	GameObject *go = new GameObject();

	std::ifstream inputFile(file, std::ios::in | std::ios::binary);
	if (inputFile.fail()) {
		delete go;
		return nullptr;
		//error("Open file error\n");
	}

	// узнаем размер файла
	inputFile.seekg(0, std::ios::end);
	long fileSize = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	// читаем данные из файла
	unsigned char *data = new unsigned char[fileSize];
	inputFile.read((char*)data, fileSize);
	inputFile.close();
	unsigned char *data_iterator = data;

	// file id
	char fileFormat[8] = "";
	char fileFormatSma[8] = "SMA";
	memcpy(fileFormat, data_iterator, sizeof(char) * 8);
	if (strcmp(fileFormat, fileFormatSma) != 0) {
		delete[] data;
		delete go;
		return nullptr;
	}
	data_iterator += sizeof(char) * 8;

	// version
	//unsigned short version = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);

	// object name
	char meshName[32] = " ";
	memcpy(meshName, data_iterator, sizeof(char) * 32);
	data_iterator += sizeof(char) * 32;

	// vertexes
	unsigned short vertexTotal = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);
	std::vector<D3DXVECTOR3> vertexes;
	if (vertexTotal) {
		for (int i = 0; i < (vertexTotal / 3); i++) {

			float *x = (float*)data_iterator; data_iterator += sizeof(float);
			float *y = (float*)data_iterator; data_iterator += sizeof(float);
			float *z = (float*)data_iterator; data_iterator += sizeof(float);

			D3DXVECTOR3 v((*x), *y, *z);

			vertexes.push_back(v);
		}
	}

	// normals
	unsigned short normalsTotal = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);
	std::vector<D3DXVECTOR3> normals;
	if (normalsTotal) {
		for (int i = 0; i < (normalsTotal / 3); i++) {

			float *x = (float*)data_iterator; data_iterator += sizeof(float);
			float *y = (float*)data_iterator; data_iterator += sizeof(float);
			float *z = (float*)data_iterator; data_iterator += sizeof(float);

			D3DXVECTOR3 n((*x), *y, *z);

			normals.push_back(n);
		}
	}

	// texture coordinates
	unsigned short uvTotal = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);
	std::vector<D3DXVECTOR2> texcoords;
	if (uvTotal > 0 && uvTotal == (vertexTotal / 3) * 2) {
		for (int i = 0; i < (uvTotal / 2); i++) {

			float *s = (float*)data_iterator; data_iterator += sizeof(float);
			float *t = (float*)data_iterator; data_iterator += sizeof(float);

			D3DXVECTOR2 uv(*s, *t);
			texcoords.push_back(uv);
		}
	}

	// textures
	std::string texName;

	unsigned short numTextures = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);

	for (int i = 0; i < numTextures; i++) {
		char textureName[64] = "default.png";
		memcpy(textureName, data_iterator, sizeof(char) * 64);
		data_iterator += sizeof(char) * 64;

		texName = textureName;
		//setup converter

		unsigned short numTriangleIndexes = *(unsigned short*)data_iterator;
		data_iterator += sizeof(unsigned short);

		for (int j = 0; j < numTriangleIndexes; j++) {
		//	unsigned short index = *(unsigned short*)data_iterator;
			// todo save indexes
			data_iterator += sizeof(unsigned short);
		}
	}

	//================================ animations =========================================
	// skeleton
	AnimatedMesh *amesh = new AnimatedMesh();
	amesh->SetTexture(texName);

	unsigned short numBones = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);

	//auto animations = new Animations();

	for (int i = 0; i < numBones; i++) {

		//short parentIdx = *(unsigned short*)data_iterator;
		data_iterator += sizeof(unsigned short);

		D3DXVECTOR3 rot, pos;
		rot.x = (*(float*)data_iterator); data_iterator += sizeof(float);
		rot.y = *(float*)data_iterator; data_iterator += sizeof(float);
		rot.z = *(float*)data_iterator; data_iterator += sizeof(float);

		pos.x = (*(float*)data_iterator); data_iterator += sizeof(float);
		pos.y = *(float*)data_iterator; data_iterator += sizeof(float);
		pos.z = *(float*)data_iterator; data_iterator += sizeof(float);

		amesh->AddBone(pos, rot);
	}

	// vertex weights
	unsigned short numVertWeights = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);

	for (int i = 0; i < numVertWeights; i++) {
		unsigned short numWeights = *(unsigned short*)data_iterator;
		data_iterator += sizeof(unsigned short);

		std::vector<AnimatedMesh::Weight> vertexWeights;
		for (int j = 0; j < numWeights; j++) {
			short boneIndex = *(unsigned short*)data_iterator;
			data_iterator += sizeof(unsigned short);

			float weight = *(float*)data_iterator;
			data_iterator += sizeof(float);

			AnimatedMesh::Bone *bone = nullptr;
			if (boneIndex >= 0 && boneIndex < (short)amesh->GetBonesNum()) {
				bone = amesh->GetBone(boneIndex);
			}
			AnimatedMesh::Weight w(bone, weight);
			vertexWeights.push_back(w);
		}
		amesh->AddVertexWeights(vertexWeights);
	}
	// animations

	unsigned short numAnimations = *(unsigned short*)data_iterator;
	data_iterator += sizeof(unsigned short);
	for (int i = 0; i < numAnimations; i++)	{

		char animName[64] = "None";
		memcpy(animName, data_iterator, sizeof(char) * 64);
		data_iterator += sizeof(char) * 64;

		auto *animation = new AnimatedMesh::Animation(animName);

		unsigned short numKeyframes = *(unsigned short*)data_iterator;
		data_iterator += sizeof(unsigned short);

		for (int j = 0; j < numKeyframes; j++) {
			AnimatedMesh::Keyframe kf;
			unsigned short keyframeIndex = *(unsigned short*)data_iterator;
			data_iterator += sizeof(unsigned short);

			kf.index = keyframeIndex;
			for (int k = 0; k < numBones; k++) {
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 position;

				rotation.x = (*(float*)data_iterator); data_iterator += sizeof(float);
				rotation.y = *(float*)data_iterator; data_iterator += sizeof(float);
				rotation.z = *(float*)data_iterator; data_iterator += sizeof(float);
				position.x = (*(float*)data_iterator); data_iterator += sizeof(float);
				position.y = *(float*)data_iterator; data_iterator += sizeof(float);
				position.z = *(float*)data_iterator; data_iterator += sizeof(float);

				kf.rotations.push_back(rotation);
				kf.positions.push_back(position);
				kf.bone.push_back(amesh->GetBone(k));
			}
			animation->AddKeyframe(kf);
		}
		amesh->AddAnimation(animation);
	}

	delete[] data;
	data_iterator = nullptr;

	if (vertexTotal != normalsTotal) {
		delete go;
		return nullptr;
	}

	go->name = meshName;

	for (size_t i = 0; i < vertexes.size(); i++) {
		VertexData vd;

		vd.position.x = vertexes[i].x;
		vd.position.y = vertexes[i].y;
		vd.position.z = vertexes[i].z;
		vd.normal.x = normals[i].x;
		vd.normal.y = normals[i].y;
		vd.normal.z = normals[i].z;
		vd.uv = texcoords[i];

		D3DXVECTOR3 pos(vertexes[i].x, vertexes[i].y, vertexes[i].z);
		D3DXVECTOR3 nor(normals[i].x, normals[i].y, normals[i].z);
		D3DXVECTOR2 uv(texcoords[i].x, texcoords[i].y);
		amesh->addVertex(pos, nor, uv);
	}

	go->SetAnimatedMesh(amesh);

	return go;
}


SmaLoader::~SmaLoader()
{
}


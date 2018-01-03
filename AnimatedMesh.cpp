#include "Precompiled.h"

D3DXMATRIX AnimatedMesh::Bone::GetLocalToWorldMatrix()
{
	D3DXMATRIX FinalMat;
	D3DXMATRIX MatTemp;  // Temp matrix for rotations.
	D3DXMATRIX MatRot;   // Final rotation matrix, applied to
						 // pMatWorld.

						 // Using the left-to-right order of matrix concatenation,
						 // apply the translation to the object's world position
						 // before applying the rotations.
	D3DXMatrixIdentity(&FinalMat);
	D3DXMatrixTranslation(&FinalMat, position.x, position.y, position.z);
	D3DXMatrixIdentity(&MatRot);

	// Now, apply the orientation variables to the world matrix

	// Produce and combine the rotation matrices.
	D3DXMatrixRotationX(&MatTemp, rotation.x);         // Pitch
	D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
	D3DXMatrixRotationY(&MatTemp, rotation.y);           // Yaw
	D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
	D3DXMatrixRotationZ(&MatTemp, rotation.z);          // Roll
	D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);

	// Apply the rotation matrices to complete the world matrix.
	D3DXMatrixMultiply(&FinalMat, &MatRot, &FinalMat);

	return FinalMat;
}


AnimatedMesh::AnimatedMesh()
{
	currentAnimation = nullptr;
	animCounter = 0;
	currentFrame = 0;
}


AnimatedMesh::~AnimatedMesh()
{
	weights.clear();

	for (auto a : animations)
		if (a != nullptr)
			delete a;

	for (auto b : bones)
		if (b != nullptr)
			delete b;
}

void AnimatedMesh::AddBone(D3DXVECTOR3 p, D3DXVECTOR3 r)
{
	auto b = new Bone(p, r);
	bones.push_back(b);
}

AnimatedMesh::Bone * AnimatedMesh::GetBone(size_t id)
{
	if (id < bones.size())
		return bones[id];
	return nullptr;
}

size_t AnimatedMesh::GetBonesNum()
{
	return bones.size();
}

void AnimatedMesh::AddVertexWeights(std::vector<Weight> w)
{
	weights.push_back(w);
}

void AnimatedMesh::AddAnimation(Animation * anim)
{
	animations.push_back(anim);
}

void AnimatedMesh::addVertex(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 uv)
{
	DxVertex v;
	v.position = pos;
	v.normal = nor;
	v.uv = uv;
	vertexes.push_back(v);

	Mesh::addVertex(pos, nor, uv);
}

void AnimatedMesh::addVertex(DxVertex ver)
{
	vertexes.push_back(ver);

	Mesh::addVertex(ver);
}

void AnimatedMesh::UpdateAnimation(float dt)
{
	if (currentAnimation == nullptr) {
		return;
	}

	if (Mesh::GetVertexesNum() != vertexes.size()) {
		return;
	}

	std::vector<Bone> bones;

	Keyframe *kf = currentAnimation->GetKeyframe(currentFrame);

	animCounter += 1;
	if (animCounter >= 1) {
		animCounter = 0;
		currentFrame++;
	}
	if (currentFrame >= currentAnimation->GetKeyframesNum()) {
		currentFrame = 0;
	}

	for (size_t i = 0; i < Mesh::vertexes.size(); i++) {
		D3DXVECTOR3 finalVecPositin(0.0f, 0.0f, 0.0f);

		for (size_t j = 0; j < weights[i].size(); j++) {
			Bone* init_bone = weights[i][j].bone;
			float weight = weights[i][j].weight;

			if (init_bone != nullptr) {
				Bone deform_bone(*(kf->GetPosition(init_bone)), *(kf->GetRotation(init_bone)));
				D3DXMATRIX bonemat;
				D3DXMATRIX initBonemat(init_bone->GetLocalToWorldMatrix());

				D3DXMatrixInverse(&bonemat, 0, &initBonemat);
				D3DXMATRIX deformbonemat = deform_bone.GetLocalToWorldMatrix();

				D3DXVECTOR3 vertPos(Mesh::vertexes[i].position);
				D3DXVec3TransformCoord(&vertPos, &vertPos, &bonemat);
				D3DXVec3TransformCoord(&vertPos, &vertPos, &deformbonemat);
				vertPos *= weight;

				finalVecPositin += vertPos;
			}
		}

		vertexes[i].position.x = finalVecPositin.x;
		vertexes[i].position.y = finalVecPositin.y;
		vertexes[i].position.z = finalVecPositin.z;
	}
}

void AnimatedMesh::BeginAnimation(std::string aname)
{
	for (auto a : animations) {
		if (a->GetName() == aname) {
			currentAnimation = a;
		}
	}
}

void AnimatedMesh::StopAnimation()
{
	for (size_t i = 0; i < vertexes.size(); i++) {
		vertexes[i] = Mesh::vertexes[i];
	}
	currentAnimation = nullptr;
}

AnimatedMesh::Animation * AnimatedMesh::getAnimation(std::string aname)
{
	for (auto a : animations) {
		if (a->GetName() == aname) {
			return a;
		}
	}
	return nullptr;
}

size_t AnimatedMesh::GetVertexesNum()
{
	return vertexes.size();
}

size_t AnimatedMesh::GetVertexSize()
{
	return sizeof(DxVertex);
}

DxVertex* AnimatedMesh::GetVertexes()
{
	return &vertexes[0];
}

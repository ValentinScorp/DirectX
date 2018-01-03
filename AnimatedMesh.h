#include "Precompiled.h"

#ifndef SOURCE_ANIMATEDMESH_H_
#define SOURCE_ANIMATEDMESH_H_

class AnimatedMesh : public Mesh
{
public:
	class Bone
	{
	public:
		Bone(D3DXVECTOR3 p, D3DXVECTOR3 r)
			:position(p), rotation(r) {}
		~Bone() {}

		D3DXMATRIX GetLocalToWorldMatrix();

	private:
		D3DXVECTOR3 position;
		D3DXVECTOR3 rotation;
	};

	class Weight
	{
	public:
		Weight(Bone *b, float w) : bone(b), weight(w) {}
		~Weight() {}

		Bone *bone;
		float weight;
	};

	class Keyframe
	{
	public:
		unsigned int index;

		std::vector<Bone*> bone;
		std::vector<D3DXVECTOR3> rotations;
		std::vector<D3DXVECTOR3> positions;

		D3DXVECTOR3* GetRotation(Bone *b) {
			for (size_t i = 0; i < bone.size(); i++) {
				if (bone[i] == b)
					return &rotations[i];
			}
			return nullptr;
		}
		D3DXVECTOR3* GetPosition(Bone *b) {
			for (size_t i = 0; i < bone.size(); i++) {
				if (bone[i] == b)
					return &positions[i];
			}
			return nullptr;
		}

		Keyframe() {
			index = 0;
		}
		~Keyframe() {}
	};


	class Animation {
	private:
		std::string name;
		std::vector <Keyframe> keyframes;

	public:
		Animation(std::string n)
			: name(n) {}
		~Animation() {}

		void AddKeyframe(Keyframe kf) {
			keyframes.push_back(kf);
		}
		std::string GetName() {
			return name;
		}
		Keyframe * GetKeyframe(size_t id) {
			return &keyframes[id];
		}

		size_t GetKeyframesNum() {
			return keyframes.size();
		}
	};

private:
	std::vector<DxVertex> vertexes;
	std::vector<Bone*>bones;
	std::vector<std::vector<Weight>> weights;

	std::vector<Animation*> animations;

	Animation *currentAnimation;

	size_t currentFrame;
	size_t animCounter;

public:
	AnimatedMesh();
	virtual ~AnimatedMesh();

	void AddBone(D3DXVECTOR3 p, D3DXVECTOR3 r);
	Bone* GetBone(size_t id);
	size_t GetBonesNum();
	void AddVertexWeights(std::vector<Weight> w);
	void AddAnimation(Animation *anim);

	virtual void addVertex(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 uv);
	virtual void addVertex(DxVertex ver);
	void UpdateAnimation(float dt);
	void BeginAnimation(std::string aname);
	void StopAnimation();

	size_t GetVertexesNum();
	size_t GetVertexSize();
	DxVertex* GetVertexes();

private:
	Animation* getAnimation(std::string aname);
};

#endif /* SOURCE_ANIMATEDMESH_H_ */

#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include "Game.h"
#include "Math.h"
#include "Utility.h"

// *** �A�N�^�[�N���X ***
class Actor {
public:
	enum class State { Active, Pause, Dead };

	Actor(class Game* game);
	virtual ~Actor(); // �f�X�g���N�^

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const uint8_t* keyState);
	virtual void UpdateActor(float deltaTime);
	virtual void ActorInput(const uint8_t* keyState);

	// �A�N�Z�b�T
	const Vec2& Get_Position() const { return mPosition; }
	void Set_Position(const Vec2& position) { mPosition = position; }
	float Get_Scale() const { return mScale; }
	void Set_Scale(float scale) { mScale = scale; }
	float Get_Rotation() const { return mRotation; }
	void Set_Rotation(float rotation) { mRotation = rotation; }
	Vec2 Get_Forward() const { return Vec2(std::cos(mRotation), -std::sin(mRotation)); }
	State Get_State() const { return mState; }
	void Set_State(State state) { mState = state; }
	class Game* Get_Game() { return mGame; }

	// �R���|�[�l���g�̒ǉ�/�폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// �A�N�^�[�̏��
	State mState;
	// �g�����X�t�H�[��
	Vec2 mPosition;
	float mScale;
	float mRotation;
	// �A�N�^�[�̃R���|�[�l���g
	std::vector<class Component*> mComponents;
	// �Q�[��
	class Game* mGame;
};
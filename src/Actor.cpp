#include "Actor.h"
#include "Component.h"

// �R���X�g���N�^
Actor::Actor(Game* game)
	: mState(EActive),
	  mPosition(Vec2::Zero),
	  mScale(1.0f),
	  mRotation(0.0f),
	  mGame(game)
{
	mGame->AddActor(this);
}

// �f�X�g���N�^
Actor::~Actor() {
	mGame->RemoveActor(this);
	// �e�R���|�[�l���g���폜
	// MEMO: ~Component��Actor�̃��\�b�h���Ăяo���̂Ŏg���Ȃ�
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

// �A�N�^�[�̍X�V
void Actor::Update(float deltaTime) {
	if (mState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

// �S�R���|�[�l���g�̍X�V
void Actor::UpdateComponents(float deltaTime) {
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

// �A�N�^�[�ŗL�̍X�V
void Actor::UpdateActor(float deltaTime) {
	// �I�[�o�[���C�h
}

// �L�[���͂̏���
void Actor::ProcessInput(const uint8_t* keyState) {
	if (mState == EActive) {
		if (mState == EActive) {
			// �S�R���|�[�l���g�̏���
			for (auto comp : mComponents) {
				comp->ProcessInput(keyState);
			}
			// �A�N�^�[�ŗL�̏���
			ActorInput(keyState);
		}
	}
}

// �A�N�^�[�ŗL�̓��͏���
void Actor::ActorInput(const uint8_t* keyState) {
	// �I�[�o�[���C�h
}

// �R���|�[�l���g�̒ǉ�
void Actor::AddComponent(Component* component) {
	// mOrder�Ɋ�Â��ʒu�ɑ}��
	int myOrder = component->Get_UpdateOrder();
	auto itr = mComponents.begin();
	while (itr != mComponents.end()) {
		if (myOrder < (*itr)->Get_UpdateOrder()) break;
		itr++;
	}
	// �}��
	mComponents.insert(itr, component);
}

// �R���|�[�l���g�̍폜
void Actor::RemoveComponent(Component* component) {
	auto itr = std::find(mComponents.begin(), mComponents.end(), component);
	if (itr != mComponents.end()) {
		mComponents.erase(itr);
	}
}
#include "Component.h"
#include "Actor.h"
#include <SDL.h>

// �R���X�g���N�^
Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner),
	  mUpdateOrder(updateOrder)
{
	// �A�N�^�[(���L��)�Ɏ��g��ǉ�
	mOwner->AddComponent(this);
}

// �f�X�g���N�^
Component::~Component() {
	// �A�N�^�[(���L��)���玩�g���폜
	mOwner->RemoveComponent(this);
}

// �X�V
void Component::Update(float deltaTime) {
	// �I�[�o�[���C�h
}

// ���͏���
void Component::ProcessInput(const uint8_t* keyState) {
	// �I�[�o�[���C�h
}
#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner) 
	:MoveComponent(owner),
	 mForwardKey(0),
	 mBackKey(0),
	 mClockwiseKey(0),
	 mCounterClockwiseKey(0),
	 mMaxForwardSpeed(0.0f),
	 mMaxAngularSpeed(0.0f)
{}

// �L�[���͂���ړ��E��]���x������
void InputComponent::ProcessInput(const uint8_t* keyState) {
	// �ړ��R���|�[�l���g�̈ړ����x��ݒ�
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey]) {
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey]) {
		forwardSpeed -= mMaxForwardSpeed;
	}
	Set_ForwardSpeed(forwardSpeed);

	// �ړ��R���|�[�l���g�̉�]���x��ݒ�
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey]) {
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey]) {
		angularSpeed -= mMaxAngularSpeed;
	}
	Set_AngularSpeed(angularSpeed);
}
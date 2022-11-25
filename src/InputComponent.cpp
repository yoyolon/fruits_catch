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

// キー入力から移動・回転速度を決定
void InputComponent::ProcessInput(const uint8_t* keyState) {
	// 移動コンポーネントの移動速度を設定
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey]) {
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey]) {
		forwardSpeed -= mMaxForwardSpeed;
	}
	Set_ForwardSpeed(forwardSpeed);

	// 移動コンポーネントの回転速度を設定
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey]) {
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey]) {
		angularSpeed -= mMaxAngularSpeed;
	}
	Set_AngularSpeed(angularSpeed);
}

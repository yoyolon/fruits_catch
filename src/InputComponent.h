#pragma once

#include "MoveComponent.h"
#include <cstdint>

// �L�[�{�[�h���͏����p�R���|�[�l���g

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	// �Q�b�^�E�Z�b�^
	float Get_MaxForwardSpeed() const { return mMaxForwardSpeed; }
	void Set_MaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }

	float Get_MaxAngularSpeed() const { return mMaxAngularSpeed; }
	void  Set_MaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }

	int Get_ForwardKey() const { return mForwardKey; }
	void Set_ForwardKey(int key) { mForwardKey = key; }

	int Get_BackKey() const { return mBackKey; }
	void Set_BackKey(int key) { mBackKey = key; }

	int Get_ClockwiseKey() const { return mClockwiseKey; }
	void Set_ClockwiseKey(int key) { mClockwiseKey = key; }

	int Get_CounterClockwiseKey() const { return mCounterClockwiseKey; }
	void Set_CounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

private:
	// �ړ��E��]���x�̍ő�l
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// �ړ��E��]�Ɋ��蓖�Ă��L�[
	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
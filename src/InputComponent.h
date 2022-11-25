#pragma once

#include "MoveComponent.h"
#include <cstdint>

// キーボード入力処理用コンポーネント

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	// ゲッタ・セッタ
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
	// 移動・回転速度の最大値
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// 移動・回転に割り当てたキー
	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
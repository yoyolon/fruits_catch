#pragma once

#include "Component.h"

class MoveComponent : public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder=10);

	void Update(float deltaTime) override;

	// ゲッタ/セッタ
	float Get_AngularSpeed() const { return mAngularSpeed; }
	float Get_ForwardSpeed() const { return mForwardSpeed; }
	void Set_AngularSpeed(float speed) { mAngularSpeed = speed; }
	void Set_ForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
	float mAngularSpeed; // 回転角速度(ラジアン)
	float mForwardSpeed; // 移動速度
};
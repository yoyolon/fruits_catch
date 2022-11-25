#pragma once

#include "Component.h"

class MoveComponent : public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder=10);

	void Update(float deltaTime) override;

	// �Q�b�^/�Z�b�^
	float Get_AngularSpeed() const { return mAngularSpeed; }
	float Get_ForwardSpeed() const { return mForwardSpeed; }
	void Set_AngularSpeed(float speed) { mAngularSpeed = speed; }
	void Set_ForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
	float mAngularSpeed; // ��]�p���x(���W�A��)
	float mForwardSpeed; // �ړ����x
};
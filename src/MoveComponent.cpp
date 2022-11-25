#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder),
	 mAngularSpeed(0.0f),
	 mForwardSpeed(0.0f)
{}

// �A�N�^�[���ړ��E��]������
void MoveComponent::Update(float deltaTIme) {
	// ��]
	if (!Math::NearZero(mAngularSpeed)) {
		float rot = mOwner->Get_Rotation();
		rot += mAngularSpeed * deltaTIme;
		mOwner->Set_Rotation(rot);
	}
	// �ړ�
	if (!Math::NearZero(mForwardSpeed)) {
		Vec2 pos = mOwner->Get_Position();
		pos += mOwner->Get_Forward() * mForwardSpeed * deltaTIme;

		// TEST: �͈͊O����
		pos.x = std::clamp(pos.x, 0.0f, float(WINDOWWIDTH));
		pos.y = std::clamp(pos.y, 0.0f, float(WINDOWHEIGHT));
		mOwner->Set_Position(pos);
	}
}
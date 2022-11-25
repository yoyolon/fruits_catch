#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder),
	 mAngularSpeed(0.0f),
	 mForwardSpeed(0.0f)
{}

// アクターを移動・回転させる
void MoveComponent::Update(float deltaTIme) {
	// 回転
	if (!Math::NearZero(mAngularSpeed)) {
		float rot = mOwner->Get_Rotation();
		rot += mAngularSpeed * deltaTIme;
		mOwner->Set_Rotation(rot);
	}
	// 移動
	if (!Math::NearZero(mForwardSpeed)) {
		Vec2 pos = mOwner->Get_Position();
		pos += mOwner->Get_Forward() * mForwardSpeed * deltaTIme;

		// TEST: 範囲外処理
		pos.x = std::clamp(pos.x, 0.0f, float(WINDOW_WIDTH));
		pos.y = std::clamp(pos.y, 0.0f, float(WINDOW_HEIGHT));
		mOwner->Set_Position(pos);
	}
}
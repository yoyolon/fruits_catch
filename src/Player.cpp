#include "Player.h"
#include "Game.h"
#include "Fruits.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include <algorithm>

// �R���X�g���N�^
Player::Player(Game* game)
	: Actor(game), mCircle(nullptr), mScore(0), mTimer(30.0f)
{
	// �v���C���[�e�N�X�`��(�{��)
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 3, 4);
	asc->Set_Texture(game->GetTexture("assets/player_walk.png"));
	asc->Change_Anim(6, 8, 8);

	// �v���C���[�e�N�X�`��(��)
	AnimSpriteComponent* ascFront = new AnimSpriteComponent(this, 3, 4, 150);
	ascFront->Set_Texture(game->GetTexture("assets/player_basket.png"));
	ascFront->Change_Anim(6, 8, 8);

	// ���͏����R���|�[�l���g�̐���
	InputComponent* inputComp = new InputComponent(this);
	inputComp->Set_ForwardKey(SDL_SCANCODE_RIGHT);
	inputComp->Set_BackKey(SDL_SCANCODE_LEFT);
	inputComp->Set_ClockwiseKey(SDL_SCANCODE_A);
	inputComp->Set_CounterClockwiseKey(SDL_SCANCODE_D);
	inputComp->Set_MaxForwardSpeed(150.0f);
	inputComp->Set_MaxAngularSpeed(0.0f * Math::Pi);

	// �~�R���|�[�l���g�̐���(�Փ˔���p)
	mCircle = new CircleComponent(this);
	mCircle->Set_Radius(8.0f); // TODO: �}�W�b�N�i���o�[�̏���
	mCircle->Set_Offset(Vec2(0.0, -10.0));
}

// �A�N�^�[�̍X�V
void Player::UpdateActor(float deltaTime) {
	// ���Ԃ̍X�V
	mTimer -= deltaTime;
	// �ʒu�̍X�V
	Vec2 pos = Get_Position();
	pos.x = std::clamp(pos.x, 0.0f, float(WINDOWWIDTH));
	Set_Position(pos);

	// �t���[�c�ƌ�������
	for (auto fruit : Get_Game()->Get_Fruits()) {
		if (Intersect(*mCircle, *(fruit->Get_Circle()))) {
			// �X�R�A�Ǝc�莞�Ԃ̒ǉ�
			Fruits::Type type = fruit->Get_Type();
			if (type == Fruits::Efruits) mScore += fruit->Get_Point();
			else if (type == Fruits::Efruits) mTimer -= fruit->Get_Point();
			// �t���[�c�̏���
			fruit->Set_State(EDead);
			break;
		}
	}
}

// �A�N�^�[�ŗL�̓��͏���(���Ƃō폜)
void Player::ActorInput(const uint8_t* keyState) {
	// ���U�[�𔭎� 	
	//if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f) { 		
	//	mLaserCooldown = 0.5f; 	
	//}
}
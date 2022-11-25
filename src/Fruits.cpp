#include "Fruits.h"
#include "CircleComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Random.h"
#include "SpriteComponent.h"

Fruits::Fruits(Game* game)
	: Actor(game), mCircle(nullptr), mType(Fruits::FruitsType::Fruits), mPoint(0)
{
	// �����_���Ȉʒu�E�����ŏ�����
	Vec2 randomPos = Random::GenVector(Vec2::Zero, Vec2(WINDOW_WIDTH, 0.0f));
	Set_Position(randomPos);
	Set_Rotation(-0.5 * Math::Pi);

	// �ړ��R���|�[�l���g�̐���
	MoveComponent* moveComp = new MoveComponent(this);
	moveComp->Set_ForwardSpeed(50.0f);

	// �X�v���C�g�R���|�[�l���g�̐���
	SpriteComponent* spriteComp = new SpriteComponent(this, 120);
	int rand = Random::GenIntRange(0, 99);
	// ��: 5%
	if (rand <= 5) {
		spriteComp->Set_Texture(game->GetTexture("assets/peach.png"));
		mPoint = 200;
		moveComp->Set_ForwardSpeed(50.0f);
	}
	// �: 25%
	else if (rand <= 30) {
		spriteComp->Set_Texture(game->GetTexture("assets/bery.png"));
		mPoint = 50;
		moveComp->Set_ForwardSpeed(150.0f);
	}
	// �ь�: 50%
	else if (rand <= 80) {
		spriteComp->Set_Texture(game->GetTexture("assets/apple.png"));
		mPoint = 20;
		moveComp->Set_ForwardSpeed(150.0f);
	}
	// �n�Y��: 15%
	else if (rand <= 95) {
		spriteComp->Set_Texture(game->GetTexture("assets/dragon.png"));
		mPoint = -100;
		moveComp->Set_ForwardSpeed(100.0f);
	}
	// �^�C�}�[: 5%
	else {
		spriteComp->Set_Texture(game->GetTexture("assets/watch.png"));
		mType = Fruits::FruitsType::Watch;
		mPoint = 5;
		moveComp->Set_ForwardSpeed(100.0f);
	}

	// �~�R���|�[�l���g�̐���(�Փ˔���p)
	mCircle = new CircleComponent(this);
	mCircle->Set_Radius(8.0f); // TODO: �}�W�b�N�i���o�[�̏���

	// �t���[�c���Q�[���ɒǉ�
	game->AddFruits(this);
}

Fruits::~Fruits() {
	Get_Game()->RemoveFruits(this);
}
#include "FruitsGenerator.h"
#include "Fruits.h"
#include "Random.h"

// �R���X�g���N�^
FruitsGenerator::FruitsGenerator(Game* game)
	: Actor(game), mTimer(0.0f), mDownTime(0.75f)
{}

// �X�V
void FruitsGenerator::UpdateActor(float deltaTime) {
	mTimer += deltaTime;
	// ��莞�Ԍo�߂Ńt���[�c�𐶐�
	if (mTimer >= mDownTime) {
		// �����_��������������
		if (mTimer - mDownTime >= Random::GenFloatRange(0.0f, 2.0f)) {
			new Fruits(this->Get_Game());
			mTimer = 0.0f;
		}
	}
}
#pragma once

#include "Actor.h"

// �t���[�c�I�u�W�F�N�g�𐶐�
class FruitsGenerator : public Actor {
public:
	FruitsGenerator(Game* game);
	// ���Ԃ̍X�V
	void UpdateActor(float deltaTime) override;

private:
	float mTimer; // �o�ߎ���
	float mDownTime; // �����\����
};

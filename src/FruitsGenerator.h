#pragma once

#include "Actor.h"

// *** �t���[�c�I�u�W�F�N�g�̃W�F�l���[�^ ***
class FruitsGenerator : public Actor {
public:
	FruitsGenerator(Game* game);
	void UpdateActor(float deltaTime) override;

private:
	float mTimer; // �o�ߎ���
	float mDownTime; // �����\����
};

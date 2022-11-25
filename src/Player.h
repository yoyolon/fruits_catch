#pragma once

#include "Actor.h"

// �v���C���[�N���X
class Player : public Actor {
public:
	Player(class Game* game);

	void UpdateActor(float DeltaTime) override;

	// �Q�b�^
	int Get_Score() const { return mScore; }
	float Get_Time() const { return mTimer; }

private:
	// TODO: �X�R�A �c�莞��
	class CircleComponent* mCircle;
	int mScore;
	float mTimer;
};
#pragma once

#include "Actor.h"

// *** �t���[�c�I�u�W�F�N�g ***
class Fruits : public Actor {
public:
	enum class FruitsType { Fruits, Watch };

	Fruits(class Game* game);
	~Fruits();
	
	void UpdateActor(float DeltaTime) override;

	// �Q�b�^
	class CircleComponent* Get_Circle() const { return mCircle; }
	int Get_Point() const { return mPoint; }
	FruitsType Get_Type() const { return mType; }

private:
	class CircleComponent* mCircle; // �Փ˔���R���|�[�l���g
	int mPoint; // ���_
	FruitsType mType; // �I�u�W�F�N�g�̎��
};
#pragma once

#include "Actor.h"

// *** �t���[�c�I�u�W�F�N�g ***
class Fruits : public Actor {
public:
	enum class FruitsType { Fruits, Watch };

	Fruits(class Game* game);
	~Fruits();

	// �Q�b�^
	class CircleComponent* Get_Circle() const { return mCircle; }
	int Get_Point() const { return mPoint; }
	FruitsType Get_Type() const { return mType; }

private:
	class CircleComponent* mCircle;
	int mPoint; // ���_
	FruitsType mType;
};
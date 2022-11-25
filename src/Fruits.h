#pragma once

#include "Actor.h"

class Fruits : public Actor {
public:
	enum Type { Efruits, Ewatch };

	Fruits(class Game* game);
	~Fruits();

	// �Q�b�^
	class CircleComponent* Get_Circle() const { return mCircle; }
	int Get_Point() const { return mPoint; }
	Type Get_Type() const { return mType; }

private:
	class CircleComponent* mCircle;
	int mPoint; // ���_
	Type mType;
};
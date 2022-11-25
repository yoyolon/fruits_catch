#pragma once

#include <random>
#include "Math.h"

// �����������N���X
class Random {
public:
	// ������
	static void Init();

	// �V�[�h
	// NOTE: �蓮�ł͎g��Ȃ�
	static void Seed(unsigned int seed);

	// ��������
	static float GenFloat();
	static float GenFloatRange(float min, float max);
	static int GenIntRange(int min, int max);
	static Vec2 GenVector(const Vec2& min, const Vec2& max);
	static Vec3 GenVector(const Vec3& min, const Vec3& max);

private:
	static std::mt19937 sGenerator;
};
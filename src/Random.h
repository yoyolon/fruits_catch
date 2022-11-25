#pragma once

#include <random>
#include "Math.h"

// 乱数を扱うクラス
class Random {
public:
	// 初期化
	static void Init();

	// シード
	// NOTE: 手動では使わない
	static void Seed(unsigned int seed);

	// 乱数生成
	static float GenFloat();
	static float GenFloatRange(float min, float max);
	static int GenIntRange(int min, int max);
	static Vec2 GenVector(const Vec2& min, const Vec2& max);
	static Vec3 GenVector(const Vec3& min, const Vec3& max);

private:
	static std::mt19937 sGenerator;
};
#include "Random.h"

void Random::Init() {
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed) {
	sGenerator.seed(seed);
}

float Random::GenFloat() {
	return GenFloatRange(0.0f, 1.0f);
}

float Random::GenFloatRange(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(sGenerator);
}

int Random::GenIntRange(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGenerator);
}

Vec2 Random::GenVector(const Vec2& min, const Vec2& max) {
	Vec2 v = Vec2(GenFloat(), GenFloat());
	return min + (max - min) * v;
}

Vec3 Random::GenVector(const Vec3& min, const Vec3& max) {
	Vec3 v = Vec3(GenFloat(), GenFloat(), GenFloat());
	return min + (max - min) * v;
}

std::mt19937 Random::sGenerator;
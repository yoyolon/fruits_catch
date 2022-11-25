#include "Utility.h"

// ‰~‚Ì•`‰æ(ƒeƒXƒg—p)
void DrawCircle(SDL_Renderer* renderer, float radius, Vec2 center, bool fill) {
	float step = 0.05f;
	for (float i = 0.0f; i < 2 * Math::Pi; i += step) {
		// ‰~‚ð•`‰æ
		if (fill) {
			float x = radius * std::cos(i);
			float y = radius * std::sin(i) + center.y;
			SDL_RenderDrawLineF(renderer, center.x - x, y, center.x + x, y);
		}
		// ‰~Žü‚ð•`‰æ
		else {
			float x = radius * std::cos(i) + center.x;
			float y = radius * std::sin(i) + center.y;
			SDL_RenderDrawPointF(renderer, x, y);
			x = (radius + 1) * std::cos(i) + center.x;
			y = (radius + 1) * std::sin(i) + center.y;
			SDL_RenderDrawPointF(renderer, x, y);
		}
	}
}
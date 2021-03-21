#ifndef RECTANGLE_COLLISION_HPP_
#define RECTANGLE_COLLISION_HPP_

#include "abcg.hpp"

class OpenGLWindow;

class RectangleCollision {
	public:
		static bool checkCollision(
				const glm::vec2 recPosition1,
				const glm::vec2 recScale1,
				const glm::vec2 recPosition2,
				const glm::vec2 recScale2);
	private:
		RectangleCollision() {}

		static bool pointIsInside(
				const glm::vec2 p,
				const glm::vec2 leftUp,
				const glm::vec2 rightUp,
				const glm::vec2 rightDown,
				const glm::vec2 leftDown);

};
#endif

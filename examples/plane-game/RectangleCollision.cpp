#include "RectangleCollision.hpp"

bool RectangleCollision::checkCollision(const glm::vec2 recPosition1, const glm::vec2 recScale1, const glm::vec2 recPosition2, const glm::vec2 recScale2) {

	glm::vec2 pA1{recPosition1.x - recScale1.x, recPosition1.y + recScale1.y};
	glm::vec2 pB1{recPosition1.x + recScale1.x, recPosition1.y + recScale1.y};
	glm::vec2 pC1{recPosition1.x + recScale1.x, recPosition1.y - recScale1.y};
	glm::vec2 pD1{recPosition1.x - recScale1.x, recPosition1.y - recScale1.y};

	glm::vec2 pA2{recPosition2.x - recScale2.x, recPosition2.y + recScale2.y};
	glm::vec2 pB2{recPosition2.x + recScale2.x, recPosition2.y + recScale2.y};
	glm::vec2 pC2{recPosition2.x + recScale2.x, recPosition2.y - recScale2.y};
	glm::vec2 pD2{recPosition2.x - recScale2.x, recPosition2.y - recScale2.y};

	return pointIsInside(pA1, pA2, pB2, pC2, pD2) ||
		pointIsInside(pB1, pA2, pB2, pC2, pD2) ||
		pointIsInside(pC1, pA2, pB2, pC2, pD2) ||
		pointIsInside(pD1, pA2, pB2, pC2, pD2) ||
		pointIsInside(pA2, pA1, pB1, pC1, pD1) ||
		pointIsInside(pB2, pA1, pB1, pC1, pD1) ||
		pointIsInside(pC2, pA1, pB1, pC1, pD1) ||
		pointIsInside(pD2, pA1, pB1, pC1, pD1);
}

bool RectangleCollision::pointIsInside(const glm::vec2 p, const glm::vec2 leftUp, const glm::vec2 rightUp, const glm::vec2 rightDown, const glm::vec2 leftDown) {
	return p.x > leftUp.x && p.x < rightUp.x && p.y > leftDown.y && p.y < leftUp.y;
}

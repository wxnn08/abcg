#include "Gap.hpp"
#include <fmt/core.h>

void Gap::initializeGL(GLuint program) {
	for(auto wallObstacle : m_wallObstacles) {
		wallObstacle->initializeGL(program);
	}
}

void Gap::paintGL() {
	for(auto wallObstacle : m_wallObstacles) {
		wallObstacle->paintGL();
	}
}

void Gap::terminateGL() {
	for(auto wallObstacle : m_wallObstacles) {
		wallObstacle->terminateGL();
	}
}

void Gap::update(float deltaTime) {
	glm::vec2 translation{0};
	for(auto wallObstacle : m_wallObstacles) {
		wallObstacle->update(deltaTime);
		translation.x += wallObstacle->m_translation.x;
		translation.y += wallObstacle->m_translation.y;
	}
	m_translation.x = translation.x / 2.0f;
	m_translation.y = translation.y / 2.0f;
}

void Gap::setupGap(glm::vec2 gapTranslation, float gapWidth, float gapHeight) {

	m_gapWidth = gapWidth;
	m_gapHeight = gapHeight;

	const glm::vec2 rightTranslation{
		gapTranslation.x + m_gapWidth/2.0f + std::abs(1.0f - (gapTranslation.x + m_gapWidth/2.0f))/2.0f,
		gapTranslation.y
	};

	const glm::vec2 leftTranslation{
		gapTranslation.x - m_gapWidth/2.0f - std::abs(-1.0f - (gapTranslation.x - m_gapWidth/2.0f))/2.0f,
		gapTranslation.y
	};

	if(m_wallObstacles[0] == nullptr) {
		m_wallObstacles[0] = new WallObstacle(rightTranslation, glm::vec2{std::abs(1.0f - rightTranslation.x), m_gapHeight});
	} else {
		m_wallObstacles[0]->setTranslation(rightTranslation);
		m_wallObstacles[0]->setScale(glm::vec2{std::abs(1.0f - rightTranslation.x), m_gapHeight});
	}
	if(m_wallObstacles[1] == nullptr) {
		m_wallObstacles[1] = new WallObstacle(leftTranslation, glm::vec2{std::abs(-1.0f - leftTranslation.x), m_gapHeight});
	} else {
		m_wallObstacles[1]->setTranslation(leftTranslation);
		m_wallObstacles[1]->setScale(glm::vec2{std::abs(-1.0f - leftTranslation.x), m_gapHeight});
	}
}

	bool Gap::belowScreen() {
	float yRight = m_wallObstacles[0]->getTranslation().y + m_wallObstacles[0]->getScale().y;
	float yLeft = m_wallObstacles[1]->getTranslation().y + m_wallObstacles[1]->getScale().y;
	return std::max(yRight, yLeft) < -1.0;
}

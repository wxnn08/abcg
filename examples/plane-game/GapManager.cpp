#include "GapManager.hpp"
#include <fmt/core.h>

void GapManager::initializeGL(GLuint program) {

	auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
	m_randomEngine.seed(seed);

	m_gaps.clear();

	m_gaps.push_back(new Gap(
				glm::vec2{std::uniform_real_distribution<float>{-0.9f, 0.9f}(m_randomEngine), 1.8f}, 
				std::uniform_real_distribution<float>{0.3f, 0.8f}(m_randomEngine), 
				std::uniform_real_distribution<float>{0.2f, 0.6f}(m_randomEngine)));

	for(auto gap : m_gaps) {
		gap->initializeGL(program);
	}
}

void GapManager::paintGL() {
	for(auto gap : m_gaps) {
		gap->paintGL();
	}
}

void GapManager::terminateGL() {
	for(auto gap : m_gaps) {
		gap->terminateGL();
	}
}

void GapManager::update(float deltaTime) {
	for(auto gap : m_gaps) {
		if(gap->belowScreen()) {
			gap->setupGap(
					glm::vec2{std::uniform_real_distribution<float>{-0.9f, 0.9f}(m_randomEngine), 1.8f}, 
					std::uniform_real_distribution<float>{0.3f, 0.8f}(m_randomEngine), 
					std::uniform_real_distribution<float>{0.2f, 0.6f}(m_randomEngine));
		}
		gap->update(m_speed * deltaTime);
	}
}

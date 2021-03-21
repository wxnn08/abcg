#ifndef GAPMANAGER_HPP_
#define GAPMANAGER_HPP_

#include <random>

#include "abcg.hpp"
#include "Gap.hpp"

class OpenGLWindow;

class GapManager {
	public:
		GapManager() {}
		void initializeGL(GLuint program);
		void paintGL();
		void terminateGL();

		void update(float deltaTime);

	private:
		friend OpenGLWindow;

		std::default_random_engine m_randomEngine;
		std::vector<Gap*> m_gaps;
		float m_speed{1};
};

#endif

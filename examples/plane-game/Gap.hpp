#ifndef GAP_HPP_
#define GAP_HPP_

#include "abcg.hpp"
#include "GameData.hpp"
#include "WallObstacle.hpp"

class GapManager;
class OpenGLWindow;

class Gap {
	public:
		Gap() { 
			setupGap(glm::vec2{0.5f, 1.0f}, 0.4f, 0.3f);
		}
		Gap(glm::vec2 gapPosition, float gapWidth, float gapHeight) {
			setupGap(gapPosition, gapWidth, gapHeight);
		}
		void initializeGL(GLuint program);
		void paintGL();
		void terminateGL();
		void update(float deltaTime);

		void setupGap(glm::vec2 gapPosition, float gapWidth, float gapHeight);
		bool belowScreen();

	private:
		friend GapManager;
		friend OpenGLWindow;

		std::array<WallObstacle*, 2> m_wallObstacles{nullptr, nullptr};
		float m_gapWidth{0};
		float m_gapHeight{0};
		glm::vec2 m_scale;
		glm::vec2 m_translation{glm::vec2(0)};
		glm::vec2 m_velocity{glm::vec2(0)};
};

#endif

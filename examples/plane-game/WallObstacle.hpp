#ifndef WALL_HPP_
#define WALL_HPP_

#include <fmt/core.h>
#include "abcg.hpp"
#include "GameData.hpp"

class OpenGLWindow;
class Gap;

class WallObstacle {
	public:
		WallObstacle() {}
		WallObstacle(glm::vec2 translation, glm::vec2 scale) {
			m_translation = translation;
			m_scale = scale;
		}
		WallObstacle(glm::vec2 translation, glm::vec2 scale, glm::vec4 color) {
			m_translation = translation;
			m_scale = scale;
			m_color = color;
		}

		void setTranslation(glm::vec2 translation);
		void setScale(glm::vec2 scale);
		void setColor(glm::vec4 color);
		glm::vec2 getTranslation();
		glm::vec2 getScale();
		glm::vec4 getColor();

		void initializeGL(GLuint program);
		void paintGL();
		void terminateGL();
		void update(float deltaTime);

	private:
		friend OpenGLWindow;
		friend Gap;

		GLuint m_program{};
		GLint m_translationLoc{};
		GLint m_colorLoc{};
		GLint m_scaleLoc{};

		GLuint m_vao{};
		GLuint m_vbo{};
		GLuint m_ebo{};

		glm::vec4 m_color{0, 0, 0, 1.0f};
		glm::vec2 m_scale{1.0f, 0.5f};
		glm::vec2 m_translation{glm::vec2(0)};
		glm::vec2 m_velocity{glm::vec2(0)};
};

#endif

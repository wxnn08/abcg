#ifndef AIRPLANE_HPP_
#define AIRPLANE_HPP_

#include "abcg.hpp"
#include "GameData.hpp"

class OpenGLWindow;

class Airplane {
	public:
		void initializeGL(GLuint program);
		void paintGL();
		void terminateGL();

		void update(const GameData &gameData, float deltaTime);

	private:
		friend OpenGLWindow;

		GLuint m_program{};
		GLint m_translationLoc{};
		GLint m_colorLoc{};
		GLint m_scaleLoc{};

		GLuint m_vao{};
		GLuint m_vbo{};
		GLuint m_ebo{};

		float m_speed{0.8f};
		glm::vec4 m_color{1};
		glm::vec2 m_scale{0.085f, 0.09f};
		glm::vec2 m_translation{glm::vec2(0, -0.6f)};
};

#endif

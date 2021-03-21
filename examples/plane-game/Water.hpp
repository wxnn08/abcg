#ifndef WATER_HPP_
#define WATER_HPP_

#include "abcg.hpp"

class OpenGLWindow;

class Water {
	public:
		void initializeGL(GLuint program);
		void paintGL(glm::vec2 resolution);
		void terminateGL();

		void update(float deltaTime);

	private:
		friend OpenGLWindow;

		GLuint m_program{};
		GLint m_colorLoc{};
		GLint m_timeLoc{};
		GLint m_resolutionLoc{};

		GLuint m_vao{};
		GLuint m_vbo{};
		GLuint m_ebo{};

		float m_speed{0.8f};
		float m_time{0};
		glm::vec4 m_color{0, 0, 1, 1};
		glm::vec2 m_resolution{};
};

#endif

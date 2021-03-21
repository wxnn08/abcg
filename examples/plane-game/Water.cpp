#include "Water.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <fmt/core.h>

void Water::initializeGL(GLuint program) {
	terminateGL();

	m_program = program;
	m_colorLoc = glGetUniformLocation(m_program, "color");
	m_timeLoc = glGetUniformLocation(m_program, "time");
	m_resolutionLoc = glGetUniformLocation(m_program, "resolution");

	std::array<glm::vec2, 4> positions{
		glm::vec2{-1.0f,1.0f},
		glm::vec2{-1.0f,-1.0f},
		glm::vec2{1.0f,-1.0f},
		glm::vec2{1.0f,1.0f}
	};

	std::array indices{
		0, 1, 2,
		0, 2, 3
	};

	// Generate VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
			GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate EBO
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
			GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Get location of attributes in the program
	GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};

	// Create VAO
	glGenVertexArrays(1, &m_vao);

	// Bind vertex attributes to current VAO
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(positionAttribute);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	// End of binding to current VAO
	glBindVertexArray(0);
}

void Water::paintGL(glm::vec2 resolution) {
	glUseProgram(m_program);

	glBindVertexArray(m_vao);

	m_resolution = resolution;
	glUniform1fv(m_timeLoc, 1, &m_time);
	glUniform2fv(m_resolutionLoc, 1, &m_resolution.x);
	glUniform4fv(m_colorLoc, 1, &m_color.r);
	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

	glUseProgram(0);
}

void Water::terminateGL() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void Water::update(float deltaTime) {
	m_time += deltaTime;
}

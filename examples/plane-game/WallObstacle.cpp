#include "WallObstacle.hpp"
#include <fmt/core.h>

#include <glm/gtx/fast_trigonometry.hpp>

void WallObstacle::initializeGL(GLuint program) {
	terminateGL();

	m_program = program;
	m_colorLoc = glGetUniformLocation(m_program, "color");
	m_scaleLoc = glGetUniformLocation(m_program, "scale");
	m_translationLoc = glGetUniformLocation(m_program, "translation");

	std::array<glm::vec2, 4> positions{
		glm::vec2{-1.0f, 1.0f},
		glm::vec2{-1.0f, -1.0f},
		glm::vec2{1.0f, 1.0f},
		glm::vec2{1.0f, -1.0f}
	};

	std::array indices{ 
		0, 1, 2,
		1, 2, 3
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

void WallObstacle::paintGL() {
	glUseProgram(m_program);

	glBindVertexArray(m_vao);

	glUniform2fv(m_scaleLoc, 1, &m_scale.x);
	glUniform2fv(m_translationLoc, 1, &m_translation.x);

	glUniform4fv(m_colorLoc, 1, &m_color.r);
	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

	glUseProgram(0);
}

void WallObstacle::terminateGL() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void WallObstacle::update(float deltaTime) {
	m_translation.y -= deltaTime;
	if(m_translation.y < -2.0f)
		m_translation.y = 2.0f;
}

void WallObstacle::setTranslation(glm::vec2 translation) {
	m_translation = translation;
}

void WallObstacle::setScale(glm::vec2 scale) {
	m_scale = scale;
}

void WallObstacle::setColor(glm::vec4 color) {
	m_color = color;
}

glm::vec2 WallObstacle::getTranslation() {
	return m_translation;
}

glm::vec2 WallObstacle::getScale() {
	return m_scale;
}

glm::vec4 WallObstacle::getColor() {
	return m_color;
}

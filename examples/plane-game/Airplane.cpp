#include "Airplane.hpp"

#include <glm/gtx/fast_trigonometry.hpp>


void Airplane::initializeGL(GLuint program) {
	terminateGL();

	m_program = program;
	m_colorLoc = glGetUniformLocation(m_program, "color");
	m_scaleLoc = glGetUniformLocation(m_program, "scale");
	m_translationLoc = glGetUniformLocation(m_program, "translation");

	std::array<glm::vec2, 22> positions{
		glm::vec2{0.0f,292.0f},
		glm::vec2{-20.0f,258.0f},
		glm::vec2{-30.0f,256.0f},
		glm::vec2{-46.0f,189.0f},
		glm::vec2{-49.0f,122.0f},
		glm::vec2{-398.0f,113.0f},
		glm::vec2{-396.0f,22.0f},
		glm::vec2{-45.0f,-13.0f},
		glm::vec2{-14.0f,-203.0f},
		glm::vec2{-133.0f,-226.0f},
		glm::vec2{-128.0f,-288.0f},
		glm::vec2{0.0f,-291.0f},
		glm::vec2{128.0f,-288.0f},
		glm::vec2{133.0f,-226.0f},
		glm::vec2{14.0f,-203.0f},
		glm::vec2{45.0f,-13.0f},
		glm::vec2{396.0f,22.0f},
		glm::vec2{398.0f,113.0f},
		glm::vec2{49.0f,122.0f},
		glm::vec2{46.0f,189.0f},
		glm::vec2{30.0f,256.0f},
		glm::vec2{20.0f,258.0f}
	};

	// Normalize
	for (auto &position :positions) {
		position /= glm::vec2{398.0f, 398.0f};
	}

	std::array indices{ 0, 1, 21,
		1, 2, 20,
		2, 20, 21,
		2, 19, 20,
		2, 3, 19,
		3, 18, 19,
		3, 4, 18,
		4, 5, 6,
		4, 6, 7,
		16, 17, 18,
		15, 16, 18,
		4, 15, 18,
		4, 7, 15,
		7, 8, 15,
		8, 14, 15,
		8, 9, 10,
		8, 10, 11,
		8, 11, 14,
		12, 13, 14,
		11, 12, 14
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

void Airplane::paintGL() {

	glUseProgram(m_program);

	glBindVertexArray(m_vao);

	glUniform2fv(m_scaleLoc, 1, &m_scale.x);
	glUniform2fv(m_translationLoc, 1, &m_translation.x);

	glUniform4fv(m_colorLoc, 1, &m_color.r);
	glDrawElements(GL_TRIANGLES, 20 * 3, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

	glUseProgram(0);
}

void Airplane::terminateGL() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void Airplane::update(const GameData &gameData, float deltaTime) {
	// Rotate
	if (gameData.m_input[static_cast<size_t>(Input::Left)]) {
		m_translation.x = m_translation.x - m_speed * deltaTime;
	}
	if (gameData.m_input[static_cast<size_t>(Input::Right)])
		m_translation.x = m_translation.x + m_speed * deltaTime;

	m_translation.x = std::clamp(m_translation.x, -1.0f+m_scale.x, 1.0f-m_scale.x);
}

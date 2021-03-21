#include "OpenGlWindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

#include "abcg.hpp"

void OpenGLWindow::initializeGL() {
	// Load a new font
	ImGuiIO &io{ImGui::GetIO()};
	auto filename{getAssetsPath() + "Inconsolata-Medium.ttf"};
	m_font = io.Fonts->AddFontFromFileTTF(filename.c_str(), 50.0f);
	m_fontSmall = io.Fonts->AddFontFromFileTTF(filename.c_str(), 25.0f);
	if (m_font == nullptr) {
		throw abcg::Exception{abcg::Exception::Runtime("Cannot load font file")};
	}

	// Create program to render the other objects
	m_objectsProgram = createProgramFromFile(getAssetsPath() + "objects.vert",
			getAssetsPath() + "objects.frag");
	m_waterProgram = createProgramFromFile(getAssetsPath() + "water.vert",
			getAssetsPath() + "water.frag");

	glClearColor(0, 0, 0, 1);

#if !defined(__EMSCRIPTEN__)
	glEnable(GL_PROGRAM_POINT_SIZE);
#endif

	// Start pseudo-random number generator
	auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
	m_randomEngine.seed(seed);


	m_gameData.m_state = State::Start;
	m_airplane.initializeGL(m_objectsProgram);
	m_gapmanager.initializeGL(m_objectsProgram);
	m_water.initializeGL(m_waterProgram);
}

void OpenGLWindow::handleEvent(SDL_Event &event) {
	// Keyboard events
	if (event.type == SDL_KEYDOWN) {
		
		if(m_gameData.m_state == State::Start) {
			m_gameData.m_state = State::Playing;
		}

		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
			m_gameData.m_input.reset(static_cast<size_t>(Input::Right));
			m_gameData.m_input.set(static_cast<size_t>(Input::Left));
		}
		if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
			m_gameData.m_input.reset(static_cast<size_t>(Input::Left));
			m_gameData.m_input.set(static_cast<size_t>(Input::Right));
		}
	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_gameData.m_input.reset(static_cast<size_t>(Input::Right));
			m_gameData.m_input.set(static_cast<size_t>(Input::Left));
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_gameData.m_input.reset(static_cast<size_t>(Input::Left));
			m_gameData.m_input.set(static_cast<size_t>(Input::Right));
		}
	}
}

void OpenGLWindow::update() {
	float deltaTime{static_cast<float>(getDeltaTime())};

	if (m_gameData.m_state == State::Scoreboard &&
			m_restartWaitTimer.elapsed() > 5) {
		restart();
		return;
	}


	if(m_gameData.m_state == State::Playing) {
		m_gapmanager.update(deltaTime);
		m_airplane.update(m_gameData, deltaTime);
		checkCollisions();
		updatePoints();
	}
	m_water.update(deltaTime);
}

void OpenGLWindow::restart() {
	m_airplane.m_translation.x = 0;
	m_lastBetweenWalls = false;
	m_gapmanager.m_speed = 1;
	m_gameData.m_score = 0;
	m_gameData.m_state = State::Start;

	m_airplane.initializeGL(m_objectsProgram);
	m_gapmanager.initializeGL(m_objectsProgram);
	m_water.initializeGL(m_waterProgram);
}

void OpenGLWindow::paintGL() {
	update();

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, m_viewportWidth, m_viewportHeight);

	m_water.paintGL(glm::vec2{m_viewportWidth, m_viewportHeight});
	m_gapmanager.paintGL();
	m_airplane.paintGL();
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();

	{
		auto size{ImVec2(320, 300)};
		auto position{ImVec2((m_viewportWidth - size.x) * 0.5f,
				(m_viewportHeight) * 0.1f)};
		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowSize(size);
		ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoInputs};
		ImGui::Begin(" ", nullptr, flags);

		if (m_gameData.m_state == State::Start) {
			ImGui::PushFont(m_font);
			ImGui::Text("Can you score");
			ImGui::Text(" %2d points ? ", m_gameData.m_targetScore);
			ImGui::Text(" ");
			ImGui::PopFont();
			ImGui::PushFont(m_fontSmall);
			ImGui::Text("  Press any key to start!");
		}
		if (m_gameData.m_state != State::Start) {
			ImGui::PushFont(m_font);
			if(m_gameData.m_score == 1)
				ImGui::Text(" %3d point", m_gameData.m_score);
			else
				ImGui::Text(" %3d points", m_gameData.m_score);
		}

		ImGui::PopFont();
		ImGui::End();
	}

	{
		auto size{ImVec2(320, 80)};
		auto position{ImVec2((m_viewportWidth - size.x) * 0.0f,
				(m_viewportHeight) * 0.92f)};
		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowSize(size);
		ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoInputs};

		ImGui::Begin("best score", nullptr, flags);

		ImGui::PushFont(m_fontSmall);
		ImGui::Text("Best score: %d points", m_gameData.m_bestScore);

		ImGui::PopFont();
		ImGui::End();
	}
}

void OpenGLWindow::resizeGL(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;

	glClear(GL_COLOR_BUFFER_BIT);
} 
void OpenGLWindow::terminateGL() {
	glDeleteProgram(m_objectsProgram);

	m_airplane.terminateGL();
	m_gapmanager.terminateGL();
	m_water.terminateGL();
}

void OpenGLWindow::checkCollisions() {
	bool collision = false;
	for(auto gap : m_gapmanager.m_gaps) {
		for(auto wallObstacle : gap->m_wallObstacles) {
			collision |= RectangleCollision::checkCollision(
					m_airplane.m_translation, 
					m_airplane.m_scale * glm::vec2{1, 0.3},
					wallObstacle->getTranslation(),
					wallObstacle->getScale());
		}
	}

	if(collision) {
		m_gameData.m_state = State::Scoreboard;
		m_restartWaitTimer.restart();
	}
}

void OpenGLWindow::updatePoints() {
	bool betweenWalls = false;
	for(auto gap : m_gapmanager.m_gaps) {
		betweenWalls |= RectangleCollision::checkCollision(
				m_airplane.m_translation, 
				m_airplane.m_scale,
				gap->m_translation,
				glm::vec2{gap->m_gapWidth, gap->m_gapHeight});
	}

	if(m_lastBetweenWalls && !betweenWalls) {
		m_gameData.m_score++;
		m_gameData.m_bestScore = std::max(m_gameData.m_score, m_gameData.m_bestScore);
		m_gameData.m_targetScore = (m_gameData.m_bestScore / 10 + 1) * 10;
		m_gapmanager.m_speed += 0.07;
	}

	m_lastBetweenWalls = betweenWalls;
}

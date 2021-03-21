#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <imgui.h>

#include <random>

#include "abcg.hpp"
#include "Airplane.hpp"
#include "GapManager.hpp"
#include "Water.hpp"
#include "RectangleCollision.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
	protected:
		void handleEvent(SDL_Event& event) override;
		void initializeGL() override;
		void paintGL() override;
		void paintUI() override;
		void resizeGL(int width, int height) override;
		void terminateGL() override;

	private:
		GLuint m_objectsProgram{};
		GLuint m_waterProgram{};

		int m_viewportWidth{};
		int m_viewportHeight{};
		bool m_lastBetweenWalls{false};

		GameData m_gameData;
		Airplane m_airplane;
		GapManager m_gapmanager;
		Water m_water;

		abcg::ElapsedTimer m_restartWaitTimer;

		ImFont* m_font{};
		ImFont* m_fontSmall{};

		std::default_random_engine m_randomEngine;

		void checkCollisions();
		void updatePoints();
		void restart();
		void update();
};

#endif

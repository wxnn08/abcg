#include <fmt/core.h>

#include "abcg.hpp"
#include "OpenGlWindow.hpp"

int main(int argc, char **argv) {
	try {
		abcg::Application app(argc, argv);

		auto window{std::make_unique<OpenGLWindow>()};
		window->setOpenGLSettings({.samples = 4, .vsync = true});
		window->setWindowSettings({.width = 600,
				.height = 600,
				.showFPS = false,
				.showFullscreenButton = false,
				.title = "Plane Game"});
		app.run(window);
	} catch (abcg::Exception &exception) {
		fmt::print(stderr, "{}\n", exception.what());
		return -1;
	}
	return 0;
}

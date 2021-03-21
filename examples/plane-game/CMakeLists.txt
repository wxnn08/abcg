project(plane-game)
add_executable(${PROJECT_NAME} Main.cpp OpenGlWindow.cpp Airplane.cpp WallObstacle.cpp Gap.cpp GapManager.cpp Water.cpp RectangleCollision.cpp)
enable_abcg(${PROJECT_NAME})

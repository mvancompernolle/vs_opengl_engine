#include "Engine.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>

Engine *Engine::engine = NULL;

Engine::Engine() {
	Engine::engine = this;

	graphics = new Graphics();
	input = new Input();
}

Engine::~Engine() {
	stop();
}

int Engine::run() {
	float dt;
	t1 = std::chrono::high_resolution_clock::now();

	while (true) {
		dt = tick();
		input->tick(dt);
		graphics->tick(dt);
	}

	return 0;
}

void Engine::stop(int exitCode) {

	delete graphics;
	delete input;

	//if (exitCode != 0)
		system("pause");

	exit(exitCode);
}

Engine* Engine::getEngine() {
	return engine;
}

float Engine::tick() {
	float dt;

	t2 = std::chrono::high_resolution_clock::now();
	dt = std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1).count();
	t1 = t2;

	return dt;
}
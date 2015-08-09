#ifndef OPENGL_ENGINE_ENGINE_H
#define OPENGL_ENGINE_ENGINE_H

#include <vector>
#include <string>
#include <chrono>

class Graphics;
class Input;

class Engine {

public:
	Engine();
	~Engine();
	int run();
	void stop(int exitCode = 0);
	static Engine *getEngine();
	float tick();

	Graphics* graphics;
	Input* input;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
	static Engine *engine;
};


#endif //OPENGL_ENGINE_ENGINE_H

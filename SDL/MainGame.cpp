#include<iostream>
#include "MainGame.h"
#include<string>
#include"Sprite.h"

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Ener any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run(){
	initSystems();
	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("could not init GLEW");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << event.motion.x << " " << event.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_sprite.draw();
	SDL_GL_SwapWindow(_window);
}
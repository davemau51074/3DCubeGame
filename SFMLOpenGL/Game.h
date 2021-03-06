#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "Player.h"
#include <string>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	bool move = false;
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	RenderWindow window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	Player m_player;
	void cubeRender(mat4 &modelRef);
	String readMethod();
	String fragmentRead();
	int lives = 5;
	sf::Clock timer;
	enum gameState {
		Playing,
		GameOver

	};
	
	gameState m_gameState = gameState::Playing;
	//std::vector2f 
	float distance = 0;

};

#endif
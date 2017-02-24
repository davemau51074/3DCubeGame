#pragma once


#include <iostream>
#include <glm/glm.hpp>

using namespace std;

class Player
{
public:
	Player(glm::vec3 pos);
	~Player();


	void update();
	void updateRot(float rot);
	void updatePos(glm::vec3 pos);

	glm::vec3 getPos();
	float getRot();

protected:

	glm::vec3 m_position;
	float m_rotation = 0;

};
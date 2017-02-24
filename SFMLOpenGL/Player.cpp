#include "Player.h"


 Player::Player(glm::vec3 pos):
	m_position(pos)
{






}

 Player::~Player()
 {
 
 
 }

 void Player::update()
 {
 
 }

 void Player::updateRot(float rotation)
 {
	 m_rotation += rotation;
 }

 void Player::updatePos(glm::vec3 pos)
 {
	 m_position += pos;
 }



 glm::vec3 Player::getPos()
 {
	 return m_position;
 }

 float Player::getRot()
 {

	 return m_rotation;

 }
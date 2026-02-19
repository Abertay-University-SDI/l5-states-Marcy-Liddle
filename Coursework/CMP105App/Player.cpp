#include "Player.h"
#include <iostream>

Player::Player()
{
	if (!m_texture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad";

	setTexture(&m_texture);
	setSize({ 36,36 });
	setCollisionBox({ {6,6}, { 24,25 } });
	setPosition({ 50,0 });
	m_isOnGround = false;
	setTextureRect({ { 0,0 }, { 24,24 } });
}

void Player::handleInput(float dt)
{
	m_acceleration = { 0,0 };

	if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
	{
		if (m_isOnGround = true)
		{
			m_velocity.y = - JUMP_FORCE;
			move({ 0, m_velocity.y });
			m_isOnGround = false;
		}
		
	}

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
		m_acceleration.x -= SPEED;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_acceleration.x += SPEED;

	if (m_input->isKeyDown(sf::Keyboard::Scancode::R))	// Reset (for debugging)
	{
		setPosition({ 50,0 });
		m_velocity = { 0,0 };
		m_isOnGround = false;
	}

	if (m_input->isKeyDown(sf::Keyboard::Scancode::F))
	{
		sf::Vector2f flagCentre = m_flag->getPosition() + m_flag->getSize() * 0.5f;
		sf::Vector2f switchCentre = m_switch->getPosition() + m_switch->getSize() * 0.5f;
		
		if ((getPosition() - flagCentre).length() <= 50.0)
		{
			std::cout << "flag pressed\n";
		}
		if ((getPosition() - switchCentre).length() <= 50.0)
		{
			m_switch->toggle();
		}

	}

}

void Player::update(float dt)
{
	// newtonian model
	m_acceleration.y += GRAVITY;
	m_velocity += dt * m_acceleration;

	m_oldPosition = getPosition();

	move(m_velocity);
}

void Player::collisionResponse(GameObject& collider)
{
	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();
	auto overlap = playerCollider.findIntersection(wallBounds);

	if (!overlap) return;

	float histBottom = m_oldPosition.y + playerCollider.size.y;
	float tileTop = wallBounds.position.y;

	if (histBottom <= tileTop) //floor
	{
		if (m_velocity.y > 0)
		{
			m_velocity.y = 0;

			setPosition({
				getPosition().x,
				collider.getPosition().y - getCollisionBox().size.y
			});
		}
	}
	else //wall
	{
		m_velocity.x *= -COEFF_RESTITUTION;
		if (playerCollider.position.x < wallBounds.position.x)
		{
			setPosition({ getPosition().x - overlap->size.x, getPosition().y });
		}
		else
		{
			setPosition({ getPosition().x + overlap->size.x, getPosition().y });
		}
	}
	
	m_isOnGround = true;

}

#pragma once

// Project Includes
#include "GridObject.h"

// Library Includes
#include <SFML/Audio.hpp>

class Player : public GridObject
{

	// Functions

public:

	Player();

	// Overriding Methods
	virtual void Input(sf::Event _gameEvent);
	virtual void Update(sf::Time _frameTime);
	

private:

	bool AttemptMove(sf::Vector2i _direction);
	

	// Data

private:

	sf::Vector2i m_pendingMove;
	sf::Sound m_playerSound;
	sf::Sound m_hitWall;
	sf::Sound m_pushBox;
	
};

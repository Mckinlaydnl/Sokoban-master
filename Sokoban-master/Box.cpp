// Project Includes
#include "Box.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Storage.h"
Box::Box()
	: GridObject()
	, m_stored(false)
	, m_storesound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_blocksMovement = true;
	m_storesound.setBuffer(AssetManager::GetSoundBuffer("audio/stored.wav"));
}

bool Box::AttemptPush(sf::Vector2i _direction)
{
	// Attempt to move the box in the given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// check if the space is empty
	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			
		}
	}

	// If empty, move there
	if (blocked == false)
	{
		bool moveSucceeded = m_level->MoveObjectTo(this, targetPos);

		// if we did sucessfully move
		if (moveSucceeded == true)
		{
			// check if we are stored
			m_stored = false;

			// Loop through the contents and see if a storage object was found

			// Check if this element in the vector is a storage object
			// By doing a dynamic cast
			for (int i = 0; i < targetCellContents.size(); ++i)
			{
				Storage* storageObject = dynamic_cast<Storage*>(targetCellContents[i]);

				// If dynamic cast succeeds, it will NOT be a nullptr
				// aka, the object IS a storage object
				if (storageObject != nullptr)
				{
					// The object IS a storage object!

					// We are stored!
					m_stored = true;

					// Check if the level is complete
					m_level->CheckComplete();
				}
			}
	
			// And change our sprite accordingly
			if (m_stored)
			{
				m_sprite.setTexture(AssetManager::GetTexture("graphics/boxStored.png"));
				m_storesound.play();

				
			}
			else
			{
				m_sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
			}
		}


		return moveSucceeded;
	}
	// if movement is blocked, do nothing, return false
	// Default
	return false;

}

bool Box::GetStored()
{
	return m_stored;
}
#ifndef INPUT_HANDLER 
#define INPUT_HANDLER

struct InputHandler
{
	bool isMovingLeft, isMovingRight, isJumping;

	void UpdateInputStatus()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) isJumping = true;
		else isJumping = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) isMovingLeft = true;
		else isMovingLeft = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) isMovingRight = true;
		else isMovingRight = false;
	}
};

#endif
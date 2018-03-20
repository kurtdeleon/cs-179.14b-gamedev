#ifndef INPUT_HANDLER 
#define INPUT_HANDLER

struct InputHandler
{
	bool isMovingLeft, isMovingRight, jumpPressed;

	void UpdateInputStatus()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) jumpPressed = true;
		else jumpPressed = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) isMovingLeft = true;
		else isMovingLeft = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) isMovingRight = true;
		else isMovingRight = false;
	}
};

#endif
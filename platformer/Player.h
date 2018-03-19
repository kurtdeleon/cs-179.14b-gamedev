#ifndef PLAYER 
#define PLAYER

#include "Properties.h"
#include "InputHandler.h"

class Player
{
private:
	sf::RectangleShape player;
	sf::RenderWindow *window;
	InputHandler *inputHandler;

	void Jump ()
	{

	}

	void Move ()
	{
		
	}

public:
	Player( sf::RenderWindow *w, InputHandler *i, sf::Vector2f *pos )
	{
		player.setSize( sf::Vector2f( PLAYER_W, PLAYER_H ) );
		player.setOrigin( PLAYER_W/2, PLAYER_H/2 );
		player.setPosition( (*pos) );
		player.setFillColor( COLOR_PLAYER );
		window = w;
		inputHandler = i;
	}
	
	void Update ()
	{
		

		
	}

	void Draw ()
	{
		window->draw( player );
	}
};

#endif
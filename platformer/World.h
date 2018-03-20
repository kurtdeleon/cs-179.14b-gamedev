#ifndef WORLD
#define WORLD

#include "Player.h"
#include "InputHandler.h"
#include "LevelData.h"

class World
{
private:
	Player *player;
	std::vector<sf::RectangleShape*> *walls;
	sf::RenderWindow *window; 
	InputHandler *inputHandler;
	
	void Initialize()
	{

	}

	void handleCollision(){
	//handle collision function?
	}
public:
	World( sf::RenderWindow *w, InputHandler *i, LevelData *ld )
	{
		player = new Player( w, i, &(ld->playerPosition) );
		walls = &(ld->walls);
		window = w;
		inputHandler = i;
	}
	
	void UpdateWorld ()
	{
		player->UpdatePlayer();
		//handleCollision();
	}

	void DrawWorld ()
	{
		for ( sf::RectangleShape* p : (*walls) )
		{
			window->draw ( ( *p ) );
		}
		player->Draw();
	}
};

#endif
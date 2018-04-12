#ifndef WORLD
#define WORLD

#include "Player.h"
#include "InputHandler.h"
#include "LevelData.h"
#include "Properties.h"
#include "Camera.h"

class World
{
private:
	Player *player;
	Camera *camera;
	std::vector<sf::RectangleShape*> *walls;
	sf::RenderWindow *window; 
	InputHandler *inputHandler;
	Properties *properties;
	sf::View *view;

	bool IsColliding( sf::FloatRect a, sf::FloatRect b )
	{
		if ( a.intersects( b ) ) return true;
		return false;
	}

	void ApplyHorizontalCollisionResponse()
	{
		for ( sf::RectangleShape* wall : (*walls) )
		{
			/* Simple collision check to see if both rects are colliding in any way. */
			/* will serve as the early out of the collision response. */
			if ( IsColliding( wall->getGlobalBounds(), player->GetAABB() ) )
			{
				player->SetVelocity ( sf::Vector2f( 0, player->GetVelocity().y ));
				float playerHorizontalPosition = player->GetPosition().x;
				float wallHorizontalPosition = wall->getPosition().x;

				float collisionResponseWidth = player->GetSize().x/2 
				+ wall->getSize().x/2 + properties->GAP;
				
				/* Player is to the LEFT of the wall.*/
				if ( playerHorizontalPosition < wallHorizontalPosition )
				{
					player->ChangePosition( wallHorizontalPosition - collisionResponseWidth,
						player->GetPosition().y);
				}
				/* Player is to the RIGHT of the wall.*/
				else if ( playerHorizontalPosition > wallHorizontalPosition )
				{
					player->ChangePosition( wallHorizontalPosition + collisionResponseWidth,
						player->GetPosition().y);
				}
			}
		}
	}

	void ApplyVerticalCollisionResponse()
	{
		/* Reset grounded status first before response. */
		/* Won't matter for movement as everything is done. */
		player->SetGroundedStatus( false );
		for ( sf::RectangleShape* wall : (*walls) )
		{
			if ( IsColliding( wall->getGlobalBounds(), player->GetAABB() ) )
			{
				player->SetVelocity ( sf::Vector2f( player->GetVelocity().x, 0 ) );
				float playerVerticalPosition = player->GetPosition().y;
				float wallVerticalPosition = wall->getPosition().y;

				float collisionResponseWidth = player->GetSize().y/2 
				+ wall->getSize().y/2 + properties->GAP;

				if ( playerVerticalPosition < wallVerticalPosition )
				{
					player->SetGroundedStatus( true );
					player->ChangePosition( player->GetPosition().x,  
						wallVerticalPosition - collisionResponseWidth );
				}
				/* Player is to the RIGHT of the wall.*/
				else if ( playerVerticalPosition > wallVerticalPosition )
				{
					player->ChangePosition( player->GetPosition().x,  
						wallVerticalPosition + collisionResponseWidth );
				}
			}
		}
	}

public:
	World( sf::RenderWindow *w, InputHandler *i, LevelData *ld, Properties *p, sf::View *v )
	{
		player = new Player( w, i, &(ld->playerPosition),p );
		camera = new Camera( w, p, v, player );
		walls = &(ld->walls);
		window = w;
		inputHandler = i;
		properties = p;
		view = v;
	}
	
	void UpdateWorld ()
	{
		player->UpdateHorizontalMovement();
		ApplyHorizontalCollisionResponse();
		player->UpdateVerticalMovement();
		ApplyVerticalCollisionResponse();
		camera->UpdateCamera();
	}

	void DrawWorld ()
	{	
		for ( sf::RectangleShape* p : (*walls) )
		{
			window->draw ( ( *p ) );
		}
		player->Draw();
		camera->UpdateAndDrawCameraGuides();
	}
};

#endif
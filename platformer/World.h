#ifndef WORLD
#define WORLD

#include "Player.h"
#include "InputHandler.h"
#include "LevelData.h"
#include "Properties.h"
#include "Camera.h"
#include "Sounds.h"
#include "Textures.h"
#include "Interface.h"

class World
{
private:
	sf::Sprite bg;
	Player *player;
	std::vector<sf::RectangleShape*> *walls;
	std::vector<sf::CircleShape*> *coins;
	sf::RenderWindow *window; 
	sf::View *view;
	Camera *camera;
	Sounds *sounds;
	Textures *textures;
	LevelData *levelData;
	InputHandler *inputHandler;
	Properties *properties;
	Interface *UI;

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

	void CoinCollision()
	{
		for (sf::CircleShape* coin : (*coins))
		{
			if ( IsColliding(coin->getGlobalBounds(), player->GetAABB()))
			{
				coin->setPosition( sf::Vector2f(-100, -100) );
				levelData->coinCounter++;
				sounds->PlaySFX( "coin" );
				levelData->CheckGameStatus();

				if ( levelData->hasWon )
				{
					sounds->PlaySFX( "victory" );
					while (sounds->victorySound.getStatus() == sf::Sound::Playing);
					levelData->PrintEndMessage();
					window->close();
				}
			}
		}
	}
	
	void CheckObjectCollisions()
	{
		CoinCollision();
	}

public:
	World( sf::RenderWindow *w, InputHandler *i, LevelData *ld, Properties *p, sf::View *v, Sounds *s, Textures *t )
	{
		player = new Player( w, i, &(ld->playerPosition), p, t, s );
		camera = new Camera( w, p, v, player );
		walls = &(ld->walls);
		coins = &(ld->coins);
		levelData = ld;
		window = w;
		inputHandler = i;
		properties = p;
		view = v;
		sounds = s;
		textures = t;
		UI = new Interface( w, coins->size() );
	}

	void InitializeWorld()
	{
		bg.setTexture( textures->bgTexture );
		bg.setTextureRect( sf::IntRect( 0, 0, properties->WINDOW_H, properties->WINDOW_W ) );
		bg.setOrigin( sf::Vector2f( properties->WINDOW_H/2, properties->WINDOW_W/2 ) );

		for ( sf::RectangleShape* p : (*walls) )
		{
			p->setTexture( &(textures->tile) );
		}

		for ( sf::CircleShape* c : (*coins))
		{
			c->setTexture( &(textures->coin) );
		}
	}
	
	void UpdateWorld ()
	{
		player->UpdateHorizontalMovement();
		ApplyHorizontalCollisionResponse();
		player->UpdateVerticalMovement();
		ApplyVerticalCollisionResponse();
		CheckObjectCollisions();
		camera->UpdateCamera();
		bg.setPosition( view->getCenter() );
		sounds->PlayMusic();
		UI->Update( levelData->coinCounter, view->getCenter() );
	}

	void DrawWorld ()
	{	
		window->draw( bg );
		
		for ( sf::RectangleShape* p : (*walls) )
		{
			window->draw ( ( *p ) );
		}

		for ( sf::CircleShape* c : (*coins))
		{
			window->draw ( ( *c ) );
		}
		
		player->Draw();

		if ( properties->cameraGuidesOn) 
		{
			camera->UpdateAndDrawCameraGuides();
		}

		UI->Draw();
	}
};

#endif
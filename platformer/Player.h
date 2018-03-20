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
	sf::Vector2f velocity,position;
	bool isJumping;
	bool isGrounded;

	void Jump ()
	{
		//check is Jump botton Pressed
		if(inputHandler->jumpPressed ){
			//if colliding downwards
			
			//isJumping = true;
			//isGrounded = false;
			position = player.getPosition();

			if(/*isJumping &&inputHandler->jumpPressed==false && */velocity.y < CUT_V_VEL + V_ACCEL){
				velocity.y = CUT_V_VEL;
				std::cout << "CUT!" << std::endl;
			}

			else velocity.y += V_ACCEL;
		}
		//maximum downwards velocity
		/*
		if (velocity.y > MAX_V_VEL)
		{
			velocity.y = MAX_V_VEL;
		}

		//apply gravity
		velocity.y += GRAVITY;
		*/

		//update and set position
		position.y += velocity.y;
		player.setPosition(position);
		std::cout << velocity.y << std::endl;
	}

	void Move ()
	{
		position = player.getPosition();
		//check if pressing Move Left button
		if(inputHandler->isMovingLeft)
		{	
			//moving right to left
			if ( velocity.x > 0){
				if(isGrounded)velocity.x += -(H_ACCEL + H_ACCEL * H_OPPOSITE);
				else velocity.x += -(H_ACCEL + H_ACCEL * H_OPPOSITE) * H_AIR;
			}
			//max speed left
			if (velocity.x < -(MAX_H_VEL) + H_ACCEL )velocity.x = -(MAX_H_VEL);
			//normal left movement
			else
			{
				if(isGrounded)velocity.x += -(H_ACCEL);
				else velocity.x += -(H_ACCEL) * H_AIR;
			}
		}
		//check if pressing Move Right button
		if(inputHandler->isMovingRight)
		{
			//moving left to right
			if ( velocity.x < 0){
				if(isGrounded)velocity.x += (H_ACCEL + H_ACCEL * H_OPPOSITE);
				else velocity.x += (H_ACCEL + H_ACCEL * H_OPPOSITE) * H_AIR;
			}
			//max speed right
			if (velocity.x > MAX_H_VEL - H_ACCEL) velocity.x = MAX_H_VEL;
			//normal right movement
			else
			{
				if(isGrounded)velocity.x += (H_ACCEL);
				else velocity.x += (H_ACCEL) * H_AIR;
			}
		}
		//Move Left and Move Right key release
		if(inputHandler->isMovingLeft == false && 
		   inputHandler->isMovingRight==false)
		{
			if(velocity.x > -(MIN_H_VEL) &&
			   velocity.x <   MIN_H_VEL )
			     velocity.x = 0;
			else velocity.x = velocity.x * H_COEFF;
		}	

		//Update and Set Position
		position.x += velocity.x;
		player.setPosition(position);
		

		std::cout << velocity.x << std::endl;
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
		//if input handler has x boolean do y
		//ex move -> move here
		Move();
		Jump();
		
		
	}

	void Draw ()
	{
		window->draw( player );
	}
};

#endif
#ifndef PLAYER 
#define PLAYER

#include <cmath>

#include "Properties.h"
#include "InputHandler.h"

class Player
{
private:
	sf::RectangleShape player;
	sf::RenderWindow *window;
	InputHandler *inputHandler;
	sf::Vector2f velocity, acceleration;

	bool isGrounded, isHoldingJump, canStillJump;
	int FC_isHoldingJump, FC_canStillJump;

	void Apply_Gravity() 
	{
		acceleration.y += GRAVITY;
	}

	void ApplyAirAccelerationMultiplier()
	{
		acceleration.x *= H_AIR;
	}

	void ApplyVelocityCoeff()
	{
		/* Clamps max horizontal velocity. */ 
		/* Clamps max horizontal velocity. */ 
		/* Clamps max horizontal velocity. */ 
		/* Clamps max horizontal velocity. */ 
		/* Clamps max horizontal velocity. */ 
		/* Clamps max horizontal velocity. */ 
		/* THIS DOESN'T FUCKING WORK DUDE */ 
		/* I TRIED EVERYTHING */ 

		velocity.x *= H_COEFF;


		printf("%f\n", velocity.x);
	}

	void ResetValues()
	{
		acceleration.x = 0;
		acceleration.y = 0;
	}

	void ClampHorizontalVelocity()
	{
		/* Clamps max horizontal velocity. */ 
		if ( velocity.x > MAX_H_VEL ) velocity.x = MAX_H_VEL;
		if ( velocity.x < -MAX_H_VEL ) velocity.x = -MAX_H_VEL;

		/* Clamps min horizontal velocity. */
		if ( std::abs( velocity.x ) <= MIN_H_VEL) velocity.x = 0;
	}

	void ClampVerticalVelocity()
	{
		/* Clamps vertical velocity. */
		if ( velocity.y > MAX_V_VEL ) velocity.y = MAX_V_VEL;
	}

	void Jump ()
	{
		if ( isHoldingJump )
		{
			velocity.y = 0;
			acceleration.y = V_ACCEL;

			FC_isHoldingJump++;
		}
	}

	void UpdateVerticalVelocity()
	{
		/* Apply vertical acceleration to velocity. */
		velocity.y += acceleration.y;
		ClampVerticalVelocity();
	}
	/* Apply called when player is moving to the Left. */
	void MoveLeft()
	{
		/* Checks if player is moving to the right. */
		/* If yes, then addition acceleration is multiplied. */
		if ( velocity.x > 0 )
		{
			acceleration.x -= (H_ACCEL * H_OPPOSITE);
		}
		else
		{
			acceleration.x -= H_ACCEL;
		}
	}

	/* Apply called when player is moving to the right. */
	void MoveRight()
	{
		/* Checks if player is moving to the left. */
		/* If yes, then addition acceleration is multiplied. */
		if ( velocity.x < 0 )
		{
			acceleration.x += (H_ACCEL * H_OPPOSITE);
		}
		else
		{
			acceleration.x += H_ACCEL;
		}
	}

	void UpdateHorizontalVelocity()
	{
		if ( !inputHandler->isMovingLeft && !inputHandler->isMovingRight )
		{
			ApplyVelocityCoeff();
		}
		else /* This means the character MUST be moving. */
		{

			if ( inputHandler->isMovingRight )
			{
				MoveRight();
			}
			else if ( inputHandler->isMovingLeft )
			{
				MoveLeft();
			}

			if ( !isGrounded )
			{
				ApplyAirAccelerationMultiplier();
			}
		}

		velocity.x += acceleration.x;
		ClampHorizontalVelocity();
	}

	void UpdatePosition()
	{
		/* Apply velocity to position. */
		player.setPosition( player.getPosition() + velocity );
	}

	void UpdateFrameCounter()
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
	
	void UpdatePlayer ()
	{
		if ( inputHandler->jumpPressed && !isGrounded )
		{
			Jump();
		}

		UpdateHorizontalVelocity();

		UpdatePosition();
		//ResetValues();
	}

	void Draw ()
	{
		window->draw( player );
	}
};

#endif
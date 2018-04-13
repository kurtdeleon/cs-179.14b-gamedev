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
	Properties *properties;
	sf::Vector2f velocity, acceleration;

	bool isGrounded, canStillJump, isSafeToJump, hasCut, hasJumped;
	int FC_isHoldingJump, FC_isSafeToJump;

	//////////////////////////////////////////////
	//////////////////////////////////////////////
	/* HORIZONTAL MOVEMENT FUNCTIONS ARE BELOW. */
	//////////////////////////////////////////////
	//////////////////////////////////////////////

	/* Applied to acceleration while not grounded (or is in air). */
	void ApplyAirAccelerationMultiplier()
	{
		acceleration.x *= properties->H_AIR;
	}

	/* Is applied when player is not moving. */
	void ApplyVelocityCoeff()
	{
		velocity.x *= properties->H_COEFF;
	}

	/* Clamps horizontal velocity. */
	void ClampHorizontalVelocity()
	{
		/* MAX_VEL */ 
		if ( velocity.x > properties->MAX_H_VEL * properties->FPS ) velocity.x = properties->MAX_H_VEL * properties->FPS;
		if ( velocity.x < -(properties->MAX_H_VEL * properties->FPS) ) velocity.x = -(properties->MAX_H_VEL * properties->FPS);

		/* MIN_VEL */
		if ( std::abs( velocity.x ) <= properties->MIN_H_VEL) velocity.x = 0;
	}

	/* Apply called when player is moving to the Left. */
	void MoveLeft()
	{
		/* Checks if player is moving to the right. */
		/* If yes, then addition acceleration is multiplied. */
		if ( velocity.x > 0 )
		{
			acceleration.x -= ((properties->H_ACCEL * properties->FPS) * properties->H_OPPOSITE);
		}
		else
		{
			acceleration.x -= properties->H_ACCEL * properties->FPS;
		}
	}

	/* Apply called when player is moving to the right. */
	void MoveRight()
	{
		/* Checks if player is moving to the left. */
		/* If yes, then addition acceleration is multiplied. */
		if ( velocity.x < 0 )
		{
			acceleration.x += ((properties->H_ACCEL * properties->FPS) * properties->H_OPPOSITE);
		}
		else
		{
			acceleration.x += properties->H_ACCEL * properties->FPS;
		}
	}

	////////////////////////////////////////////
	////////////////////////////////////////////
	/* VERTICAL MOVEMENT FUNCTIONS ARE BELOW. */
	////////////////////////////////////////////
	////////////////////////////////////////////

	void ApplyGravity() 
	{
		acceleration.y += properties->GRAVITY * properties->FPS;
	}

	/* Clamps vertical velocity. */
	void ClampVerticalVelocity()
	{
		/* Clamp when plpayer is going down. */
		if ( velocity.y > properties->MAX_V_VEL * properties->FPS ) velocity.y = properties->MAX_V_VEL * properties->FPS;
	}

	void Jump ()
	{
		velocity.y = 0;
		acceleration.y += properties->V_ACCEL * properties->FPS;
	}

	void UpdateFrameCounters()
	{
		if ( inputHandler->jumpPressed )
		{
			FC_isHoldingJump++;

			/* Checks if it is still possible to jump. */
			if ( FC_isHoldingJump > properties->V_HOLD )
			{
				canStillJump = false;
				hasJumped = true;
			}
			else 
			{
				canStillJump = true;
			}

			if ( !isGrounded && !hasJumped )
			{
				FC_isSafeToJump++;

				if ( FC_isSafeToJump > properties->V_SAFE )
				{
					isSafeToJump = false;
				}
				else 
				{
					isSafeToJump = true;
				}
			}
			else
			{
				FC_isSafeToJump = 0;
				isSafeToJump = true;
			}
		}
		else 
		{
			if ( isGrounded )
			{
				hasJumped = false;
			}

			if ( canStillJump && FC_isHoldingJump > 0 )
			{
				hasCut = true;
			}
			else 
			{
				hasCut = false;
				FC_isHoldingJump = 0;
			}
		}
	}

public:
	Player( sf::RenderWindow *w, InputHandler *i, sf::Vector2f *pos, Properties *p )
	{
		player.setSize( sf::Vector2f( (p->PLAYER_W), (p->PLAYER_H) ) );
		player.setOrigin( (p->PLAYER_W)/2, (p->PLAYER_H)/2 );
		player.setPosition( (*pos) );
		player.setFillColor( sf::Color(255, 240, 255) );
		window = w;
		inputHandler = i;
		properties = p;
		canStillJump = false;
		hasCut = false;
		isGrounded = false;
		isSafeToJump = false;
		FC_isSafeToJump = 0;
		FC_isHoldingJump = 0;
	}

	bool IsGrounded()
	{
		return isGrounded;
	}

	sf::Vector2f GetPosition()
	{
		return player.getPosition();
	}

	sf::FloatRect GetAABB()
	{
		return player.getGlobalBounds();
	}

	sf::Vector2f GetSize()
	{
		return player.getSize();
	}

	sf::Vector2f GetVelocity()
	{
		return velocity;
	}

	void SetVelocity( sf::Vector2f newVelocity )
	{
		velocity = newVelocity;
	}

	void ChangePosition ( float x, float y )
	{
		player.setPosition( x, y );
	}

	void SetGroundedStatus ( bool grounded )
	{
		isGrounded = grounded;
	}

	void UpdateHorizontalMovement()
	{
		if ( !inputHandler->isMovingLeft && !inputHandler->isMovingRight )
		{
			acceleration.x = 0.f;
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

		ChangePosition ( player.getPosition().x + velocity.x, player.getPosition().y );
	}

	void UpdateVerticalMovement()
	{
		UpdateFrameCounters();

		/* Check if player is jumping. If not, set acceleration to 0. */
		if ( inputHandler->jumpPressed && canStillJump && isSafeToJump && !hasJumped )
		{
			Jump();
		}
		else if ( hasCut )
		{
			velocity.y = properties->CUT_V_VEL * properties->FPS;
			FC_isHoldingJump = 0;
			acceleration.y = 0;
			hasCut = false;
		}
		else
		{
			acceleration.y = 0;
		}

		/* Apply gravity to player. */
		ApplyGravity();

		/* Apply vertical acceleration to velocity. */
		velocity.y += acceleration.y;
		ClampVerticalVelocity();
		
		/* Change position of player. */
		ChangePosition ( player.getPosition().x, player.getPosition().y + velocity.y );
	}

	void Draw ()
	{
		window->draw( player );
	}
};

#endif
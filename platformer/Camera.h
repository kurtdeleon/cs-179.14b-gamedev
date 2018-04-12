#ifndef CAMERA
#define CAMERA

#include "Player.h"
#include "Properties.h"

class Camera
{
private:
	Player *player;
	sf::RenderWindow *window; 
	Properties *properties;
	sf::View *view;

	void PositionLock()
	{
		view->setCenter( player->GetPosition() );
	}

	void EdgeSnap()
	{
		sf::Vector2f halfSize = view->getSize()/2.f;
		sf::Vector2f viewCenter = view->getCenter();
		sf::Vector2u windowSize = window->getSize();
		float offset = 250;

		/* Horizontal Snap */
		if( viewCenter.x - halfSize.x < 0 )
		{
			view->setCenter( offset, viewCenter.y );
		}
		else if( viewCenter.x + halfSize.x > windowSize.x )
		{
			view->setCenter( windowSize.x - offset, viewCenter.y );
		}

		/* Refresh viewCenter */
		viewCenter = view->getCenter();

		/* Vertical Snap */
		if( viewCenter.y - halfSize.y < 0 )
		{
			view->setCenter( viewCenter.x, offset );
		}
		else if( viewCenter.y + halfSize.y > windowSize.y )
		{
			view->setCenter( viewCenter.x, windowSize.y - offset );
		}
	}

	void DrawCameraGuides()
	{	
		switch ( properties->CAM_TYPE )
		{
			case 0:
			//TODO draw code goes here
			break;

			case 1:
			//TODO draw code goes here
			break;

			case 2:
			//TODO draw code goes here
			break;

			case 3:
			//TODO draw code goes here
			break;

			case 4:
			//TODO draw code goes here
			break;
		}
	}

	void UpdateCamera()
	{
		switch ( properties->CAM_TYPE )
		{
			case 0:
			PositionLock();
			break;

			case 1:
			PositionLock();
			EdgeSnap();
			break;

			case 2:
			break;

			case 3:
			break;

			case 4:
			break;
		}
	}

public:
	Camera( sf::RenderWindow *w, Properties *p, sf::View *v, Player *pl )
	{
		window = w; 
		properties = p;
		view = v;
		player = pl;
	}

	void UpdateView()
	{
		UpdateCamera();
		if ( properties->cameraGuidesOn ) 
		{
			DrawCameraGuides();
		}
	}
};

#endif
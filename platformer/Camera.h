#ifndef CAMERA
#define CAMERA

#include "Player.h"
#include "Properties.h"
#include <cmath>

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

	/*
	void EdgeSnap()
	{
		sf::Vector2f halfSize = view->getSize()/2.f;
		sf::Vector2f viewCenter = view->getCenter();
		sf::Vector2u windowSize = window->getSize();
		float offset = 250;

		// Horizontal Snap
		if( viewCenter.x - halfSize.x < 0 )
		{
			view->setCenter( halfSize.x, viewCenter.y );
		}
		else if( viewCenter.x + halfSize.x > windowSize.x )
		{
			view->setCenter( windowSize.x - halfSize.x, viewCenter.y );
		}

		// Refresh viewCenter
		viewCenter = view->getCenter();

		// Vertical Snap
		if( viewCenter.y - halfSize.y < 0 )
		{
			view->setCenter( viewCenter.x, halfSize.y );
		}
		else if( viewCenter.y + halfSize.y > windowSize.y )
		{
			view->setCenter( viewCenter.x, windowSize.y - halfSize.y );
		}
	}
	*/
		void EdgeSnap()
	{
		//sf::Vector2f halfSize = view->getSize()/2.f;
		sf::Vector2f viewCenter = view->getCenter();
		//sf::Vector2u windowSize = window->getSize();

		// Horizontal Snap
		if( viewCenter.x  < properties->CAM_EDGES[0] )
		{
			view->setCenter( properties->CAM_EDGES[0], viewCenter.y );
		}
		else if( viewCenter.x  > properties->CAM_EDGES[2] )
		{
			view->setCenter( properties->CAM_EDGES[2], viewCenter.y );
		}

		// Refresh viewCenter
		viewCenter = view->getCenter();

		// Vertical Snap
		if( viewCenter.y  < properties->CAM_EDGES[1] )
		{
			view->setCenter( viewCenter.x, properties->CAM_EDGES[1] );
		}
		else if( viewCenter.y > properties->CAM_EDGES[3] )
		{
			view->setCenter( viewCenter.x, properties->CAM_EDGES[3] );
		}
	}
	

	/*void EdgeSnap()
	{
		sf::Vector2f viewCenter = view->getCenter();
		sf::Vector2f newCenter;

		if ( viewCenter.x < properties->CAM_EDGES[0] )
		{
			newCenter.x = properties->CAM_EDGES[0];
		}
		else if ( viewCenter.x > properties->CAM_EDGES[2] )
		{
			newCenter.x = properties->CAM_EDGES[2];
		}

		if ( viewCenter.y < properties->CAM_EDGES[1] )
		{
			newCenter.y = properties->CAM_EDGES[1];
		}
		else if ( viewCenter.y > properties->CAM_EDGES[3] )
		{
			newCenter.y = properties->CAM_EDGES[3];
		}

		view->setCenter( newCenter );

	}*/

	/*void EdgeSnap()
	{
		sf::FloatRect cam = cameraWindow.getGlobalBounds();

		sf::Vector2f viewCenter = view->getCenter();
		sf::Vector2f newCenter;

		if ( viewCenter.x < cam.left )
		{
			newCenter.x = cam.left;
		}
		else if ( viewCenter.x > cam.left + cam.width )
		{
			newCenter.x = cam.left + cam.width;
		}

		if ( viewCenter.y < cam.top )
		{
			newCenter.y = cam.top;
		}
		else if ( viewCenter.y > cam.top + cam.height )
		{
			newCenter.y = cam.top + cam.height;
		}

		view->setCenter( newCenter );
	}*/

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

		/*cameraWindow.setSize ( sf::Vector2f(abs(properties->CAM_EDGES[0] - properties->CAM_EDGES[2]), abs(properties->CAM_EDGES[1] - properties->CAM_EDGES[3])) );
		cameraWindow.setOrigin( cameraWindow.getSize().x/2, cameraWindow.getSize().y/2 );
		cameraWindow.setPosition( sf::Vector2f(0, 0) );*/
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
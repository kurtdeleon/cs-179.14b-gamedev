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

	sf::Vector2f cameraWindowHalfSize;
	sf::RectangleShape cameraWindow,eSnap,plHor,plVert;
	sf::Vector2f currentOffset;

	void PositionLock()
	{
		view->setCenter( player->GetPosition() );
	}

	void EdgeSnap()
	{
		sf::Vector2f viewCenter = view->getCenter();

		/* Horizontal Snapping */
		if( viewCenter.x  < properties->CAM_EDGES[0] )
		{
			view->setCenter( properties->CAM_EDGES[0], viewCenter.y );
		}
		else if( viewCenter.x  > properties->CAM_EDGES[2] )
		{
			view->setCenter( properties->CAM_EDGES[2], viewCenter.y );
		}

		/* Refresh viewCenter */
		viewCenter = view->getCenter();

		/* Vertical Snapping */
		if( viewCenter.y  < properties->CAM_EDGES[1] )
		{
			view->setCenter( viewCenter.x, properties->CAM_EDGES[1] );
		}
		else if( viewCenter.y > properties->CAM_EDGES[3] )
		{
			view->setCenter( viewCenter.x, properties->CAM_EDGES[3] );
		}
	}

	void CameraWindow()
	{
		/* For Code Readability Purposes */
		sf::Vector2f cameraCenter = view->getCenter();
		sf::Vector2f playerHalfSize = player->GetSize()/2.f;
		sf::Vector2f playerPos = player->GetPosition();

		float cameraLeft = cameraCenter.x - cameraWindowHalfSize.x;
		float cameraRight = cameraCenter.x + cameraWindowHalfSize.x;
		float cameraTop = cameraCenter.y - cameraWindowHalfSize.y;
		float cameraBottom = cameraCenter.y + cameraWindowHalfSize.y;

		float playerLeft = playerPos.x - playerHalfSize.x;
		float playerRight = playerPos.x + playerHalfSize.x;
		float playerTop = playerPos.y - playerHalfSize.y;
		float playerBottom = playerPos.y + playerHalfSize.y;

		/* Horizontal response */
		if( cameraLeft > playerLeft )
		{
			currentOffset.x += playerLeft - cameraLeft;
		}
		else if( cameraRight < playerRight )
		{
			currentOffset.x += playerRight - cameraRight;
		}

		/* Vertical response */
		if( cameraTop > playerTop )
		{
			currentOffset.y += playerTop - cameraTop;
		}
		else if( cameraBottom < playerBottom )
		{
			currentOffset.y += playerBottom - cameraBottom;
		}
	}

	void CW_Normal()
	{
		/* Move actual view */
		view->move( currentOffset );
		currentOffset = sf::Vector2f(0, 0);
	}

	float GetDistance( sf::Vector2f a, sf::Vector2f b )
	{
		return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
	}

	sf::Vector2f Normalize ( sf::Vector2f a )
	{
		float length = sqrt( (a.x * a.x) + (a.y * a.y) );

		if (length != 0) return sf::Vector2f( a.x / length, a.y / length );
		return a;
	}

	void CW_WithPositionSnapping()
	{
		if ( currentOffset == sf::Vector2f(0, 0) )
		{
			sf::Vector2f direction = Normalize( player->GetPosition() - view->getCenter() );
			float distance = GetDistance( view->getCenter(), player->GetPosition() );

			if ( distance < properties->CAM_DRIFT )
			{
				view->setCenter( player->GetPosition() );
			}
			else
			{
				view->move( direction * properties->CAM_DRIFT ); 
			}
		}
		else
		{
			CW_Normal();
		}
	}

	void CW_WithPlatformSnapping()
	{
		if ( currentOffset == sf::Vector2f(0, 0) && player->IsGrounded() )
		{
			float distance = player->GetPosition().y - view->getCenter().y;

			if ( abs(distance) > 0 && abs(distance) > properties->CAM_DRIFT )
			{
				if ( distance > 0 )
				{
					view->move( 0, properties->CAM_DRIFT ); 
				}
				else
				{
					view->move( 0, -(properties->CAM_DRIFT) ); 
				}
			}
			else if ( abs(distance) > 0 && abs(distance) < properties->CAM_DRIFT )
			{
				view->setCenter( view->getCenter().x, player->GetPosition().y );
			}
		}
		else
		{
			CW_Normal();
		}
	}

public:
	Camera( sf::RenderWindow *w, Properties *p, sf::View *v, Player *pl )
	{
		window = w; 
		properties = p;
		view = v;
		player = pl;

		plVert.setSize(sf::Vector2f(1.f,120.f));
		plVert.setOrigin(sf::Vector2f((plVert.getSize().x) / 2,(plVert.getSize().y) / 2));
		plVert.setFillColor(sf::Color::Red);

		plHor.setSize(sf::Vector2f(120.f,1.f));
		plHor.setOrigin(sf::Vector2f((plHor.getSize().x) / 2,(plHor.getSize().y) / 2));
		plHor.setFillColor(sf::Color::Red);

		cameraWindowHalfSize = sf::Vector2f( abs(properties->CAM_EDGES[0] - properties->CAM_EDGES[2])/2.f,
			abs(properties->CAM_EDGES[1] - properties->CAM_EDGES[3])/2.f);

		
		sf::Vector2f halfView(sf::Vector2f(view->getSize().x/2.f,view->getSize().y/2.f));
						
		eSnap.setSize(sf::Vector2f(view->getSize().x + abs(properties->CAM_EDGES[0] -properties->CAM_EDGES[2])-10.f,view->getSize().y + abs(properties->CAM_EDGES[1]-properties->CAM_EDGES[3]) - 10.f));
		eSnap.setOrigin(sf::Vector2f(eSnap.getSize().x/2.f,eSnap.getSize().y/2.f));
		eSnap.setFillColor(sf::Color::Transparent);
		eSnap.setOutlineColor( sf::Color::Red);
		eSnap.setOutlineThickness(10); 
	

		cameraWindow.setSize( sf::Vector2f(cameraWindowHalfSize.x * 2, cameraWindowHalfSize.y * 2) );
		cameraWindow.setOrigin( sf::Vector2f(cameraWindowHalfSize.x, cameraWindowHalfSize.y) );
		cameraWindow.setFillColor ( sf::Color::Transparent );
		cameraWindow.setOutlineColor ( sf::Color(255, 240, 255) );
		cameraWindow.setOutlineThickness ( 10 );
	}

	void UpdateAndDrawCameraGuides()
	{	
		switch ( properties->CAM_TYPE )
		{
			case 0:
			//TODO draw code goes here
			plVert.setPosition(view->getCenter());
			plHor.setPosition(view->getCenter());
			if (properties->cameraGuidesOn) 
				window->draw(plVert);
				window->draw(plHor);
			break;

			case 1:
			//TODO draw code goes here
			eSnap.setPosition(sf::Vector2f(window->getSize().x/2.f,window->getSize().y/2.f));
			if (properties->cameraGuidesOn) window->draw(eSnap);
			break;

			case 2: case 3: case 4:
			cameraWindow.setPosition( view->getCenter() );
			if (properties->cameraGuidesOn) window->draw(cameraWindow);
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
			CameraWindow();
			CW_Normal();
			break;
			case 3:
			CameraWindow();
			CW_WithPositionSnapping();
			break;
			case 4:
			CameraWindow();
			CW_WithPlatformSnapping();
			break;
		}

		window->setView(*view);
	}
};

#endif
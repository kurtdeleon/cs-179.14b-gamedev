#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "World.h"
#include "LevelData.h"
#include "Properties.h"


void Initialize( std::string dataFile, LevelData &levelData, sf::RenderWindow &window )
{
	/* Creates an ifstream. */
	std::ifstream inFile;
	inFile.open( dataFile );

	/* Prints if the level file is not found. */
	if ( !inFile )
	{
		printf( "File not found. Program is closing.\n" );
		inFile.close();
		window.close();
	}
	
	/* Reads player position. */
	inFile >> levelData.playerPosition.x >> levelData.playerPosition.y;

	/* Reads the walls positions and sizes. */
	int numberOfWalls;
	inFile >> numberOfWalls;
	for ( int i = 0; i < numberOfWalls; i++ )
	{
		sf::Vector2f pos, size;
		inFile >> pos.x >> pos.y;
		inFile >> size.x >> size.y;
		sf::RectangleShape* rect = new sf::RectangleShape( size );
		rect->setFillColor( sf::Color(50, 50, 50) );
		rect->setOrigin( size.x/2, size.y/2 );
		rect->setPosition( pos );

		levelData.walls.push_back( rect );
	}

	inFile.close();
}

void setProperties( std::string dataFile, Properties &properties, sf::RenderWindow &window ){
	std::ifstream inFile;
	inFile.open( dataFile );

	if ( !inFile )
	{
		printf( "File not found. Program is closing.\n" );
		inFile.close();
		window.close();
	}

	inFile >> properties.FPS >> properties.PLAYER_H >> properties.PLAYER_W  >> properties.H_ACCEL >> properties.H_COEFF >> properties.H_OPPOSITE
	>> properties.H_AIR >> properties.MIN_H_VEL >> properties.MAX_H_VEL >> properties.GRAVITY >> properties.V_ACCEL >> properties.V_HOLD
	>> properties.V_SAFE >> properties.CUT_V_VEL >> properties.MAX_V_VEL >> properties.GAP;

	inFile >> properties.CAM_TYPE;
	inFile >> properties.CAM_EDGE1 >> properties.CAM_EDGE2 >> properties.CAM_EDGE3 >> properties.CAM_EDGE4;
	inFile >> properties.CAM_DRIFT;

	inFile.close();
}

int main ( int argc, char** argv )
{
	/* Initalizes the window. */
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800,600), "I WANT TO DIE", sf::Style::Default, settings);
	window.setFramerateLimit(60.0f);
	window.setKeyRepeatEnabled(false);
	window.setActive(true);

	/* Creates an InputHandler object. */
	InputHandler inputHandler;

	/* Reads level data from a text file. */
	LevelData levelData;
	Initialize ( argv[1], levelData, window );

	/*Reads properties from a text file. */
	Properties properties;
	setProperties( argv[2], properties, window );

	//initiallizes view (800 x 600 for the purpose of testing)
	sf::View view( sf::FloatRect( 0, 0, 500, 500 ) );

	/* Creates a World object. */
	World world( &window, &inputHandler, &levelData, &properties, &view );

	while(window.isOpen())
	{
		/* Checks if user wants to close game. */
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ( event.type == sf::Event::Closed || 
				(event.type == sf::Event::KeyPressed && 
					event.key.code == sf::Keyboard::Escape) )
			{ 
				window.close();
			}

			if ( event.type == sf::Event::KeyPressed && 
				event.key.code == sf::Keyboard::BackSlash )
			{
				properties.ToggleCameraGuides();
			}
		}

		/* Main runner loop functions below. */

		/* Updates the input status of the game. */
		inputHandler.UpdateInputStatus();

		/* Refreshes the window. */
		window.clear(sf::Color(40, 40, 40));

		/* Updates World values and draws it. */
		world.UpdateWorld();
		world.DrawWorld();

		/* Displays the game. */
		window.display();
	}
}
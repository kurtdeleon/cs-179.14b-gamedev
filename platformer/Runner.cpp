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

void setProperties(std::string dataFile, Properties &properties, sf::RenderWindow &window){
	std::ifstream inFile;
	inFile.open( dataFile );

	if ( !inFile )
	{
		printf( "File not found. Program is closing.\n" );
		inFile.close();
		window.close();
	}
	inFile >> properties.FPS;
	inFile >> properties.PLAYER_H;
	inFile >> properties.PLAYER_W ;
	inFile >> properties.H_ACCEL;
	inFile >> properties.H_COEFF;
	inFile >> properties.H_OPPOSITE;
	inFile >> properties.H_AIR;
	inFile >> properties.MIN_H_VEL;
	inFile >> properties.MAX_H_VEL;
	inFile >> properties.GRAVITY;
	inFile >> properties.V_ACCEL;
	inFile >> properties.V_HOLD;
	inFile >> properties.V_SAFE;
	inFile >> properties.CUT_V_VEL;
	inFile >> properties.MAX_V_VEL;
	inFile >> properties.GAP;

	inFile.close();
}

int main ( int argc, char** argv )
{
	/* Initalizes the window. */
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800,600), "I WANT TO DIE", sf::Style::Default, settings);
	window.setFramerateLimit(60.0f);
	window.setKeyRepeatEnabled(true);
	window.setActive(true);

	/* Creates an InputHandler object. */
	InputHandler inputHandler;

	/* Reads level data from a text file. */
	LevelData levelData;
	Initialize ( argv[1], levelData, window );

	Properties properties;
	setProperties(argv[2], properties, window );

	/* Creates a World object. */
	World world( &window, &inputHandler, &levelData, &properties );

	while(window.isOpen())
	{
		/* Checks if user wants to close game. */
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || 
				(event.type == sf::Event::KeyPressed && 
					event.key.code == sf::Keyboard::Escape))
			{ 
				window.close();
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
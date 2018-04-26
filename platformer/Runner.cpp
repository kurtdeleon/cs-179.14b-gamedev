#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "World.h"
#include "LevelData.h"
#include "Properties.h"


void Initialize( std::string dataFile, LevelData &levelData, sf::RenderWindow &window, sf::Texture &texture, sf::Texture &texture2 )
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
		rect->setTexture(&texture);
		rect->setFillColor( sf::Color(60, 40, 50) );
		rect->setOrigin( size.x/2, size.y/2 );
		rect->setPosition( pos );

		levelData.walls.push_back( rect );
	}

	int numberOfCoins;
	inFile >> numberOfCoins;
	for ( int i = 0; i < numberOfCoins; i++){
		sf::Vector2f pos;
		float rad;
		inFile >> pos.x >> pos.y;
		inFile >> rad;
		sf::CircleShape* circ = new sf::CircleShape( rad );
		//circ->setFillColor( sf::Color::Yellow );
		circ->setTexture(&texture2);
		circ->setOrigin( rad/2, rad/2 );
		circ->setPosition( pos );

		levelData.coins.push_back( circ );
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

	float frames;
	inFile >> frames;
	inFile >> properties.PLAYER_H >> properties.PLAYER_W  >> properties.H_ACCEL >> properties.H_COEFF >> properties.H_OPPOSITE
	>> properties.H_AIR >> properties.MIN_H_VEL >> properties.MAX_H_VEL >> properties.GRAVITY >> properties.V_ACCEL >> properties.V_HOLD
	>> properties.V_SAFE >> properties.CUT_V_VEL >> properties.MAX_V_VEL >> properties.GAP;

	inFile >> properties.CAM_TYPE;
	inFile >> properties.CAM_EDGES[0] >> properties.CAM_EDGES[1] >> properties.CAM_EDGES[2] >> properties.CAM_EDGES[3];
	inFile >> properties.CAM_DRIFT;

	properties.FPS = frames;
	properties.H_ACCEL /= frames;
	properties.MAX_H_VEL /= frames;
	properties.GRAVITY /= frames;
	properties.MAX_V_VEL /= frames;
	properties.V_ACCEL /= frames;
	properties.CUT_V_VEL /= frames;

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


	/* initializes music, sounds, and textures */
	sf::Music music;
	if( !music.openFromFile("music.wav")){
		window.close();
	}
	music.setLoop(true);
	music.setVolume(50.f);

	sf::Sound coinsound;
	sf::SoundBuffer coinbuffer;
	if(!coinbuffer.loadFromFile("item_pickup.flac")){
		window.close();
	}
	coinsound.setBuffer(coinbuffer);

	sf::Texture bg;
		if (!bg.loadFromFile("background.png"))
		{
			window.close();
		}
	sf::Sprite bground(bg);
	bground.setTextureRect(sf::IntRect(0, 0, 800, 600));
	bground.setOrigin(sf::Vector2f(400,300));

	sf::Texture tiles;
		if(!tiles.loadFromFile("tiles.jpg"))
		{
			window.close();
		}
	tiles.setSmooth(true);
	tiles.setRepeated(true);

	sf::Texture coin;
		if(!coin.loadFromFile("coins.png"))
		{
			window.close();
		}
	coin.setSmooth(true);

	sf::Texture playertex;
		if(!playertex.loadFromFile("idle.gif"))
		{
			window.close();
		}
	playertex.setSmooth(true);

	

	/* Creates an InputHandler object. */
	InputHandler inputHandler;

	/* Reads level data from a text file. */
	LevelData levelData;
	Initialize ( argv[1], levelData, window, tiles, coin );

	/*Reads properties from a text file. */
	Properties properties;
	setProperties( argv[2], properties, window );

	/* Initializes View */
	sf::View view;
	view.setCenter( sf::Vector2f(0, 0) );
	view.setSize( sf::Vector2f(800, 600) );
	
	/* Creates a World object. */
	World world( &window, &inputHandler, &levelData, &properties, &view, &playertex );

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
				music.stop();
				coinsound.stop();
				window.close();
			}

			if ( event.type == sf::Event::KeyPressed && 
				event.key.code == sf::Keyboard::BackSlash )
			{
				properties.ToggleCameraGuides();
			}
		}

		/* Main runner loop functions below. */

		if(music.getStatus()== sf::SoundSource::Playing)
		{
		}
		else{
			music.play();
		}
		

		/* Updates the input status of the game. */
		inputHandler.UpdateInputStatus();

		/* Refreshes the window. */
		window.clear(sf::Color(40, 40, 40));

		/* Updates World values and draws it. */
		bground.setPosition(view.getCenter());
		window.draw(bground);
		world.UpdateWorld();
		world.DrawWorld();
		

		/* Displays the game. */
		window.display();
	}
}
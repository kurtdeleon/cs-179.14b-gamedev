#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define FPS 60
#define C_RADIUS 20
#define WINDOW_H 600
#define WINDOW_W 800
#define SPEED 500.0f / FPS
#define MIN_DIST C_RADIUS * 4.0f
#define ATN 5.0f

using namespace std;
using namespace sf;

RenderWindow window;
SoundBuffer buffer;
Sound sound;

void printCommands() {
	cout << "Available Commands:" << endl;
	cout << "W / A / S / D - Move source" << endl;
	cout << "I / J / K / L - Move listener" << endl;
	cout << "SPACE - Pause/Play sound" << endl;
	cout << "R - Print available commands" << endl << endl;
}

void initialize( string soundTitle, CircleShape* listener, CircleShape* source )
{
	if (!buffer.loadFromFile( soundTitle ) )
	{
		cout << "'" << soundTitle << "' not found." << endl;
		window.close();
	}
	else
	{
		cout << "Sound successfully loaded." << endl << endl;
		
		listener->setRadius(C_RADIUS);
		listener->setOrigin(C_RADIUS, C_RADIUS);
		listener->setPosition(400, 400);
		listener->setFillColor(Color::Blue);
		
		source->setRadius(C_RADIUS);
		source->setOrigin(C_RADIUS, C_RADIUS);
		source->setPosition(400, 150);
		source->setFillColor(Color::Yellow);
		
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.setMinDistance(MIN_DIST);
		sound.setAttenuation(ATN);
		sound.play();

		printCommands();
	}
}

void checkBorderCollision( CircleShape* c )
{
	float posX = c->getPosition().x;
	float posY = c->getPosition().y;
	if (posY - C_RADIUS < 0) 				c->setPosition(posX, C_RADIUS);
	else if (posY + C_RADIUS > WINDOW_H) 	c->setPosition(posX, WINDOW_H - C_RADIUS);
	if (posX - C_RADIUS < 0)				c->setPosition(C_RADIUS, posY);
	else if (posX + C_RADIUS > WINDOW_W)	c->setPosition(WINDOW_W - C_RADIUS, posY);
}

void updateValues( CircleShape* listener, CircleShape* source )
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) listener->move(0, -SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) listener->move(-SPEED, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) listener->move(0, SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) listener->move(SPEED, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) source->move(0, -SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) source->move(-SPEED, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) source->move(0, SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) source->move(SPEED, 0);

	checkBorderCollision(listener);
	checkBorderCollision(source);

	sound.setPosition(source->getPosition().x, source->getPosition().y, 0 );
	Listener::setPosition(listener->getPosition().x, listener->getPosition().y, 0);
}

int main( int argc, char** argv )
{
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Audio Spatialization", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setActive(true);
	window.setKeyRepeatEnabled(true);

	//initialize objects
	CircleShape* listener = new CircleShape();
	CircleShape* source = new CircleShape();
	initialize(argv[1], listener, source);
	
	while(window.isOpen())
	{
		updateValues(listener, source);

		//check if window is closed
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{ 
				sound.stop();
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					sound.stop();
					window.close();
				}
				else if (event.key.code == Keyboard::Space)
				{
					if(sound.getStatus() == sf::SoundSource::Playing) 
					{
						sound.pause();
						cout << "Sound paused." << endl;
					}
					else 
					{
						sound.play();
						cout << "Sound resumed." << endl;
					}
				}
				else if (event.key.code == Keyboard::R)
				{
					printCommands();
				}
			}
		}
		//draw the vids and display
		window.clear(Color::Black);
		window.draw(*listener);
		window.draw(*source);
		window.display();
	}
}
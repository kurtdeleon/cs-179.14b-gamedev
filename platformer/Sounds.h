#ifndef SOUNDS 
#define SOUNDS

#include <string>

class Sounds
{
private:
	sf::RenderWindow *window;
	sf::Music music;
	sf::Sound coinSound;
	sf::SoundBuffer coinBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer jumpBuffer;
	sf::SoundBuffer victoryBuffer;

public:
	sf::Sound victorySound;

	Sounds( sf::RenderWindow *w )
	{
		window = w;

		if( !music.openFromFile("./resources/sfx/music.wav")){
			window->close();
		}
		music.setLoop( true );
		music.setVolume( 10.f );

		if(!coinBuffer.loadFromFile("./resources/sfx/coin.wav")){
			window->close();
		}
		coinSound.setBuffer( coinBuffer );
		coinSound.setVolume( 50.f );

		if(!jumpBuffer.loadFromFile("./resources/sfx/jump.wav")){
			window->close();
		}
		jumpSound.setBuffer( jumpBuffer );
		jumpSound.setVolume( 50.f );

		if(!victoryBuffer.loadFromFile("./resources/sfx/victory.wav")){
			window->close();
		}
		victorySound.setBuffer( victoryBuffer );
		victorySound.setVolume( 50.f );
	}

	void PlayMusic()
	{
		if( music.getStatus() != sf::SoundSource::Playing)
		{
			music.play();
		}
	}

	void PlaySFX( std::string title )
	{
		if ( title == "coin" )
		{
			coinSound.play();
		}
		else if ( title == "jump" )
		{
			jumpSound.play();
		}
		else if ( title == "victory" )
		{
			victorySound.play();
		}
	}

	void StopAll()
	{
		music.stop();
		coinSound.stop();
		jumpSound.stop();
	}
};

#endif
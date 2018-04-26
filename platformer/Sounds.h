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

public:
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
			//play sfx
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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define keyMPlay Keyboard::Space
#define keyMRestart Keyboard::LShift
#define keyMUpPitch Keyboard::W
#define keyMDownPitch Keyboard::S
#define keyMUpVol Keyboard::D
#define keyMDownVol Keyboard::A
#define keyHelp Keyboard::H
#define keySPlay Keyboard::C
#define keySUpPitch Keyboard::E
#define keySDownPitch Keyboard::Q
#define keySUpVol Keyboard::R
#define keySDownVol Keyboard::F
#define keyClose Keyboard::Escape

RenderWindow window;
Music music;
Sound sound;
SoundBuffer buffer;

void helpme(){
	cout << endl << endl << "Command List" << endl << "-------------------" << endl;
	cout << "MUSIC COMMANDS" << endl;
	cout << "Play/Pause: Space" << endl;
	cout << "Restart: Shift" << endl;
	cout << "Increase Pitch: W" << endl;
	cout << "Decrease Pitch: S" << endl;
	cout << "Increase Volume: D" << endl;
	cout << "Decrease Volume: A" << endl << endl;
	cout << "-------------------" << endl << endl;
	cout << "SOUND COMMANDS" << endl;
	cout << "Play/Pause: C" << endl;
	cout << "Increase Pitch: E" << endl;
	cout << "Decrease Pitch: Q" << endl;
	cout << "Increase Volume: R" << endl;
	cout << "Decrease Volume: F" << endl << endl;
	cout << "Command List: H" << endl;
	cout << "Exit: Escape" << endl << "-------------------" << endl << endl;

}

void initialize(string m, string s){
	if( !music.openFromFile(m)) cout << "'" << m << "' not found." << endl;
	else cout << m << " successfully loaded!" << endl;
	if(!buffer.loadFromFile(s)) cout << "'" << s << "' not found." << endl;
	else cout << s << " succesfully loaded!" << endl;

	sound.setBuffer(buffer);
	music.setLoop(true);
	helpme();
}

int main(int argc, char** argv){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(800, 600), "musix", Style::Default, settings);
	window.setFramerateLimit(60);
	window.setActive(true);
	window.setKeyRepeatEnabled(false);

	initialize(argv[1], argv[2]);

	while(window.isOpen()){
		//check if window is closed
		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){ 
				music.stop();
				sound.stop();
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == keyClose){
					music.stop();
					sound.stop();
					window.close();
				}

				if (event.key.code == keyMPlay){
					if(music.getStatus()== sf::SoundSource::Playing) music.pause();
					else music.play();
				}

				if (event.key.code == keyHelp) helpme();

				if (event.key.code == keyMRestart){
					music.stop();
					music.play();
				}

				if (event.key.code == keyMUpPitch){
					music.setPitch(music.getPitch()+0.1f);
					cout << "Music pitch is " << music.getPitch() << endl;
				}

				if (event.key.code == keyMDownPitch){
					if(music.getPitch() < 0.2) music.setPitch(0.1);
					else music.setPitch(music.getPitch()-0.1f);
					cout << "Music pitch is " << music.getPitch() << endl;
				}

				if (event.key.code == keyMUpVol){
					if(music.getVolume()>95 || music.getVolume()==95) music.setVolume(100);
					else music.setVolume(music.getVolume()+2.5f);
					cout << "Music volume is " << music.getVolume() << endl;
				}

				if (event.key.code == keyMDownVol){
					if(music.getVolume()<2.5 || music.getVolume()==2.5 ) music.setVolume(0);
					else music.setVolume(music.getVolume()-2.5f);
					cout << "Music volume is " << music.getVolume() << endl;
				}

				if (event.key.code == keySPlay){
					sound.play();
					cout << "Sound is playing" << endl;
				}

				if (event.key.code == keySUpPitch){
					sound.setPitch(sound.getPitch()+0.1f);
					cout << "Sound pitch is " << sound.getPitch() << endl;
				}

				if (event.key.code == keySDownPitch){
					if(sound.getPitch()<0.2) sound.setPitch(0.1);
					else sound.setPitch(sound.getPitch()-0.1f);
				}
				cout << "Sound pitch is " << sound.getPitch() << endl;

				if (event.key.code == keySUpVol){
					if(sound.getVolume()>95 || sound.getVolume()==95) sound.setVolume(100);
					else sound.setVolume(sound.getVolume()+2.5f);
					cout << "Sound volume is " << sound.getVolume() << endl;
				}

				if (event.key.code == keySDownVol){
					if(sound.getVolume() <2.5 || sound.getVolume() == 2.5 ) sound.setVolume(0);
					else sound.setVolume(sound.getVolume()-2.5f);

					cout << "Sound volume is " << sound.getVolume() << endl;
				}
			}
		}
		window.display();
	}
}

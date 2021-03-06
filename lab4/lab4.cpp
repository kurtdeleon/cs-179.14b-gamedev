#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


using namespace std;
using namespace sf;

//Music Keys
#define keyMPlay Keyboard::Space
#define keyMRestart Keyboard::LShift
#define keyMUpPitch Keyboard::W
#define keyMDownPitch Keyboard::S
#define keyMUpVol Keyboard::D
#define keyMDownVol Keyboard::A

//Help Key
#define keyHelp Keyboard::H

//Sound Keys
#define keySPlay Keyboard::C
#define keySUpPitch Keyboard::E
#define keySDownPitch Keyboard::Q
#define keySUpVol Keyboard::R
#define keySDownVol Keyboard::F

#define keyClose Keyboard::Escape


RenderWindow window;
Font font;
int soundcounter= 0;


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


int main(int argc, char *argv[]){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(800, 600), "musix", Style::Default, settings);
	window.setFramerateLimit(60);
	window.setActive(true);
	window.setKeyRepeatEnabled(false);

	cout << "loading music..." << endl << "loading sounds..." << endl;
	
	Music music;
	Sound sound[32];
	SoundBuffer buffer;

	//initializes music
	if( !music.openFromFile(argv[1])){
		//failed to load music file :(
		cout << "ERROR: MUSIC HAS FAILED TO LOAD" << endl;
	}
	else cout<< "Music successfully loaded!" << endl;

	//initializes sound buffer
	
	if(!buffer.loadFromFile(argv[2])){
		//failed to load sound file :(
		cout << "ERROR: SOUND HAS FAILED TO LOAD" << endl;
	}
	else cout << "Sound succesfully loaded!" <<endl;
	//initializes sound
	for(int i = 0; i <31; i++)
    {sound[i].setBuffer(buffer);}

	music.setLoop(true);

	helpme();

	while(window.isOpen()){
		//check if window is closed
		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ 
            	music.stop();
            	for(int i = 0; i <31; i++)
            			{
            	sound[i].stop();
            		}
            	window.close();}
        	if (event.type == sf::Event::KeyPressed)
            	{
            		if (event.key.code == keyClose){
            		music.stop();
            		for(int i = 0; i <31; i++)
            			{
            		sound[i].stop();
            			}
            			cout << "Goodbye!" << endl;
            		window.close();
            		}
            		if (event.key.code == keyMPlay){
            			if(music.getStatus()== sf::SoundSource::Playing ){
							music.pause();
							cout << "Music has been paused" << endl;
						}
						else{
						music.play();
						cout << "Music is playing!" << endl;
						}
					}
                	if (event.key.code == keyHelp){helpme();}
                	if (event.key.code == keyMRestart){
                		music.stop();
						music.play();
						cout << "Music has been restarted!" << endl;
					}
               	 	if (event.key.code == keyMUpPitch){
               	 		music.setPitch(music.getPitch()+0.1);
						cout << "Music pitch is now " << music.getPitch() << endl;
					}
                	if (event.key.code == keyMDownPitch){
                		if(music.getPitch() < 0.2){
                			music.setPitch(0.1f);
                		}
                		else music.setPitch(music.getPitch()-0.1);
						cout << "Music pitch is now " << music.getPitch() << endl;
					}
                	if (event.key.code == keyMUpVol){
						if(music.getVolume()>95.f || music.getVolume()==95.f ){
						music.setVolume(100.f);}
						else music.setVolume(music.getVolume()+2.5f);
						cout << "Music volume is now " << music.getVolume() << endl;
					}
            		if (event.key.code == keyMDownVol){
						if(music.getVolume()<2.5f || music.getVolume()==2.5f ){
						music.setVolume(0);}
						else music.setVolume(music.getVolume()-2.5f);
						cout << "Music volume is now " << music.getVolume() << endl;
					}
            		if (event.key.code == keySPlay){
            			if(soundcounter == 31){
            				sound[soundcounter].play();		
            				cout << "Sound[" << soundcounter <<"] is playing" << endl;
            				soundcounter = 0;
            			}
            			else{sound[soundcounter].play();
            			cout << "Sound[" << soundcounter <<"] is playing" << endl;
            			soundcounter++;
            			}
            			
					}
            		if (event.key.code == keySUpPitch){
            			for(int i = 0; i <31; i++)
            			{
            			sound[i].setPitch(sound[i].getPitch()+0.1);
						}
						cout << "Sound pitch is now " << sound[0].getPitch() << endl;
					}
            		if (event.key.code == keySDownPitch){
            			for(int i = 0; i <31; i++)
            			{
            			if(sound[i].getPitch()<0.2){
                			sound[i].setPitch(0.1);
                		}
            			else sound[i].setPitch(sound[i].getPitch()-0.1);
            		}
						cout << "Sound pitch is now " << sound[0].getPitch() << endl;
					}
            		if (event.key.code == keySUpVol){
            			for(int i = 0; i <31; i++)
            			{
						if(sound[i].getVolume()>95.f || sound[i].getVolume()==95.f){
						sound[i].setVolume(100.f);}
						else sound[i].setVolume(sound[i].getVolume()+2.5f);
						}
						cout << "Sound volume is now " << sound[0].getVolume() << endl;
					}
            		if (event.key.code == keySDownVol){
            			for(int i = 0; i <31; i++)
            			
{						if(sound[i].getVolume()<2.5f || sound[i].getVolume() ==2.5f ){
						sound[i].setVolume(0);}
						else sound[i].setVolume(sound[i].getVolume()-2.5f);
					}
						cout << "Sound volume is now " << sound[0].getVolume() << endl;
					}
            	}
        }

		window.clear(Color::Black);

		window.display();
	}
	return 0;
}
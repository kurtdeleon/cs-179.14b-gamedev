#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


using namespace std;
using namespace sf;

//Keys
#define keyPlay Keyboard::Space
#define keyLUp Keyboard::W
#define keyLDown Keyboard::S
#define keyLLeft Keyboard::D
#define keyLRight Keyboard::A
#define keyHelp Keyboard::H
#define keySUp Keyboard::C
#define keySDown Keyboard::E
#define keySLeft Keyboard::Q
#define keySRight Keyboard::R

#define keyClose Keyboard::Escape

CircleShape listener, source;
RenderWindow window;
Font font;


void helpme(){
	cout << endl << endl << "Command List" << endl << "-------------------" << endl;
	cout << "Play/Pause: Space" << endl;
	cout << "Listener Move Up: W" << endl;
	cout << "Listener Move Down: S" << endl;
	cout << "Listener Move Right: D" << endl;
	cout << "Listener Move Left: A" << endl << endl;
	cout << "Source Move Up: " << endl;
	cout << "Source Move Down: " << endl;
	cout << "Source Move Left: E" << endl;
	cout << "Source Move Right: Q" << endl << endl;
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
	

	Sound sound;
	SoundBuffer buffer;

	listener.setRadius(20);
	listener.setOrigin(20, 20);
	listener.setFillColor(Color::Magenta);
	listener.setPosition(800/2, 600/2);

	source.setRadius(20);
	source.setOrigin(20, 20);
	source.setFillColor(Color::Blue);
	source.setPosition(400, 500);


	//initializes sound buffer
	
	if(!buffer.loadFromFile(argv[1])){
		//failed to load sound file :(
		cout << "ERROR: SOUND HAS FAILED TO LOAD" << endl;
	}
	else cout << "Sound succesfully loaded!" <<endl;
	//initializes sound
	
    sound.setBuffer(buffer);

	sound.setLoop(true);

	helpme();

	while(window.isOpen()){
		//check if window is closed
		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ 
               	sound.stop();	
            	window.close();}
        	if (event.type == sf::Event::KeyPressed)
            	{
            		if (event.key.code == keyClose){
            		sound.stop();	
            			cout << "Goodbye!" << endl;
            		window.close();
            		}
            		/*
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
					}*/
            	}
        }

		window.clear(Color::Black);
		window.draw(listener);
		window.draw(source);
		window.display();
	}
	return 0;
}
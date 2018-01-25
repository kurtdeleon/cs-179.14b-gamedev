#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

RenderWindow window;

int steps, numberOfControlPoints;
float percentageSteps;
VertexArray controlPoints(LineStrip, 0);

void getInputs(){
	//initialize structures
	cin >> steps >> numberOfControlPoints;
	percentageSteps = 1/steps;
	//controlPoints.resize(numberOfControlPoints);

	//fill in vertex array
	Vector2f temp;
	for (int i = 0; i < numberOfControlPoints; i++){
		cin >> temp.x >> temp.y;
		controlPoints.append(temp);
	}
}

int main(void){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(800, 600), "CURVEY BOYES", Style::Default, settings);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setActive(true);

	getInputs();

	//controls
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::Closed:
				window.close();
				break;
				case Event::KeyPressed:
				switch(event.key.code){
					case Keyboard::Escape:
					window.close();
					break;
				}
				break;
				case Event::KeyReleased:
				switch(event.key.code){
				}
				break;
			}
		}

		window.clear(Color::Black);
		window.draw(controlPoints);
		window.display();
	}
}
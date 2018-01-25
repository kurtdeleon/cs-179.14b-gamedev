#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

RenderWindow window;

int steps, numberOfControlPoints;
float percentageSteps;
vector<Vector2f> controlPoints;
vector<VertexArray> interpolatedPoints;

void getInputs(){
	cin >> steps >> numberOfControlPoints;
	percentageSteps = 1.0f / steps;
	Vector2f temp;
	for (int i = 0; i < numberOfControlPoints; i++){
		cin >> temp.x >> temp.y;
		controlPoints.push_back(temp);
	}
}

Vector2f getSteppedPoint(Vector2f a, Vector2f b, float t){
	return a + (t * (b - a));
}

VertexArray LERP(Vector2f a, Vector2f b, Vector2f c){
	VertexArray tempLERP(LineStrip);
	tempLERP.append(a);
	for (int i = 1; i < steps; i++){
		float ps = percentageSteps * (float) i;
		Vector2f x = getSteppedPoint(a, b, ps);
		Vector2f y = getSteppedPoint(b, c, ps);
		tempLERP.append(getSteppedPoint(x, y, ps));
	}
	tempLERP.append(c);
	return tempLERP;
}

void computeForCurves(){
	for (int i = 0; i < numberOfControlPoints-2; i+=2){
		interpolatedPoints.push_back(LERP(controlPoints[i], controlPoints[i+1], controlPoints[i+2]));
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
	computeForCurves();

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear(Color::Black);
		for (VertexArray bezierCurves : interpolatedPoints){
			window.draw(bezierCurves);
		}
		window.display();
	}
}
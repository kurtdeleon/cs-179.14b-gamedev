#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

RenderWindow window;

struct ControlPoint {
	Vector2f pos;
	CircleShape circle;

	ControlPoint(Vector2f x){
		pos = x;
		circle.setRadius(5);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(pos);
	}

	Vector2f getPos() { return pos; }
	void offsetPos(Vector2f offset) { 
		pos -= offset;
		circle.setPosition(pos);
	}
	void drawCircle() { window.draw(circle); }
	bool isClicked(Vector2f mousePos) { 
		return circle.getGlobalBounds().contains(mousePos);
	}
};

int steps, numberOfControlPoints, selectedCircle;
float percentageSteps;
bool hasSelectedACircle;
vector<ControlPoint> arrayOfControlPoints;
vector<VertexArray> interpolatedPoints;
Vector2f previousMousePosition;

void initialize(){
	hasSelectedACircle = false;
	selectedCircle = 0;
	previousMousePosition = Vector2f(Mouse::getPosition(window));
	cin >> steps >> numberOfControlPoints;
	percentageSteps = 1.0f / steps;
	Vector2f temp;
	for (int i = 0; i < numberOfControlPoints; i++){
		cin >> temp.x >> temp.y;
		ControlPoint cp{temp};
		arrayOfControlPoints.push_back(cp);
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
		interpolatedPoints.push_back(LERP(arrayOfControlPoints[i].getPos(), 
			arrayOfControlPoints[i+1].getPos(), arrayOfControlPoints[i+2].getPos()));
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

	initialize();
	computeForCurves();

	while(window.isOpen()){
		//check if window is closed
		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

		//check for mouse status
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (hasSelectedACircle){
				arrayOfControlPoints[selectedCircle].offsetPos(
					arrayOfControlPoints[selectedCircle].getPos() 
					- Vector2f(Mouse::getPosition(window)));
				computeForCurves();
			}
			else {
				for (int i = 0; i < numberOfControlPoints; i++){
					if (arrayOfControlPoints[i].isClicked(Vector2f(Mouse::getPosition(window)))){
						hasSelectedACircle = true;
						selectedCircle = i;
					}
				}
			}
		}
		else {
			hasSelectedACircle = false;
		}

		previousMousePosition = Vector2f(Mouse::getPosition(window));

		window.clear(Color::Black);
		for (VertexArray bezierCurves : interpolatedPoints){ window.draw(bezierCurves); }
		for (ControlPoint cp : arrayOfControlPoints){ cp.drawCircle(); }
		window.display();
	}
}
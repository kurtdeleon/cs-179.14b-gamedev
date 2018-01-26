#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

RenderWindow window;
Font font;

struct ControlPoint {
	Vector2f pos;
	CircleShape circle;
	Text text;

	ControlPoint(Vector2f x, int y){
		pos = x;
		circle.setRadius(5);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(pos);
		circle.setFillColor(Color::Green);
		text.setFont(font);
		text.setString(to_string(y+1));
		text.setCharacterSize(12);
		text.setFillColor(Color::Green);
		text.setPosition(pos + Vector2f(12, -10));
	}

	Vector2f getPos() { return pos; }
	void offsetPos(Vector2f offset) { 
		pos -= offset;
		circle.setPosition(pos);
		text.setPosition(pos + Vector2f(12, -10));
	}
	void drawCircle() { window.draw(circle); }
	void drawText() { window.draw(text); }
	bool isClicked(Vector2f mousePos) { return circle.getGlobalBounds().contains(mousePos); }
};

int steps, numberOfControlPoints, selectedCircle;
float percentageSteps;
bool hasSelectedACircle;
vector<ControlPoint> arrayOfControlPoints;
vector<VertexArray> interpolatedPoints;
Vector2f previousMousePosition;

//gets all the inputs and sets all the values used
void initialize(){
	hasSelectedACircle = false;
	selectedCircle = 0;
	previousMousePosition = Vector2f(Mouse::getPosition(window));
	font.loadFromFile("pixelmix.ttf");
	cin >> steps >> numberOfControlPoints;
	percentageSteps = 1.0f / steps;
	Vector2f temp;
	for (int i = 0; i < numberOfControlPoints; i++){
		cin >> temp.x >> temp.y;
		ControlPoint cp{temp, i};
		arrayOfControlPoints.push_back(cp);
	}
}

//gets the "stepped" point between two points
Vector2f getSteppedPoint(Vector2f a, Vector2f b, float t){
	return a + (t * (b - a));
}

//this returns the interpolated points among 3 points
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
	window.setActive(true);

	initialize();
	computeForCurves();

	while(window.isOpen()){
		//check if window is closed
		Event event;
		while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
        }

		//check for mouse status
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (hasSelectedACircle){
				//check for mouse position delta
				arrayOfControlPoints[selectedCircle].offsetPos(
					arrayOfControlPoints[selectedCircle].getPos() 
					- Vector2f(Mouse::getPosition(window)));
				interpolatedPoints.clear();	
				computeForCurves();
			}
			else {
				//try to detect if mouse is clicking something
				for (int i = 0; i < numberOfControlPoints; i++){
					if (arrayOfControlPoints[i].isClicked(Vector2f(Mouse::getPosition(window)))){
						hasSelectedACircle = true;
						selectedCircle = i;
					}
				}
			}
		}
		else { //this means that mouse isn't being used at all
			hasSelectedACircle = false;
		}
		previousMousePosition = Vector2f(Mouse::getPosition(window));

		window.clear(Color::Black);
		for (VertexArray bezierCurves : interpolatedPoints){ window.draw(bezierCurves); }
		for (ControlPoint cp : arrayOfControlPoints){ 
			cp.drawCircle(); 
			cp.drawText();
		}
		window.display();
	}
}
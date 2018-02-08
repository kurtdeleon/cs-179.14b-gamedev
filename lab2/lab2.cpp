#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

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

int orderOfCurve, steps, numberOfControlPoints, selectedCircle;
float percentageSteps;
bool hasSelectedACircle;
Vector2f previousMousePosition;
vector<ControlPoint> arrayOfControlPoints;
vector<VertexArray> curves;
vector<vector<float>> pascalData;

//made this to replace factorial overflow :-----)
vector<int> pascalBoye(int order){
	vector<int> pascalVec;
	pascalVec.push_back(1);
	for (int i = 0; i < order; i++){
		pascalVec.push_back(pascalVec.back()*(float)((float)(order-i)/(float)(i+1)));
	}
	cout << pascalVec.size() << endl;
	return pascalVec;
}

//build data for computations
//only builds data for step 1 to step n-1
//assumes first/last step are just the first/last points
void buildData(){
	vector<int> pb = pascalBoye(orderOfCurve);
	cout << pb[0] << " " << pb[1] << " " << pb[2] << " " << pb[3] << endl;
	for (int i = 1; i < steps; i++){
		vector<float> tempVec;
		for (int j = 0; j <= orderOfCurve; j++){
			tempVec.push_back(pb[j] * 
				pow(1-(percentageSteps*i), orderOfCurve-j) * 
				pow((percentageSteps*i), j));
		};
		pascalData.push_back(tempVec);
	}
}

//gets all the inputs and sets all the values used
void initialize(){
	hasSelectedACircle = false;
	selectedCircle = 0;
	previousMousePosition = Vector2f(Mouse::getPosition(window));
	font.loadFromFile("pixelmix.ttf");
	cin >> orderOfCurve >> steps >> numberOfControlPoints;
	percentageSteps = 1.0f / steps;
	buildData(); //build data
	Vector2f temp; //filling control points data structure
	for (int i = 0; i < numberOfControlPoints; i++){
		cin >> temp.x >> temp.y;
		ControlPoint cp{temp, i};
		arrayOfControlPoints.push_back(cp);
	}
}

//computation of curves
VertexArray getCurveSegment(vector<Vector2f> points){
	VertexArray curveSegment(LineStrip);
	curveSegment.append(points.front());
	for (vector<float> vf : pascalData){
		Vector2f temp;
		for (int i = 0; i < vf.size(); i++){
			temp += vf[i] * points[i];
		}
		curveSegment.append(temp);
	}
	curveSegment.append(points.back());
	return curveSegment;
}

void computeForBezierCurve(){
	vector<Vector2f> lineSegment;
	for (int i = 0; i < numberOfControlPoints-1; i+=orderOfCurve){
		lineSegment.clear();
		for (int j = 0; j <= orderOfCurve; j++){ 
			lineSegment.push_back(arrayOfControlPoints[i+j].getPos()); 
		}
		curves.push_back(getCurveSegment(lineSegment));
	}
}

int main(void){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(800, 600), "CURVEY BOYES 2", Style::Default, settings);
	window.setFramerateLimit(60);
	window.setActive(true);

	initialize();
	computeForBezierCurve();

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
				curves.clear();	
				computeForBezierCurve();
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
		for (VertexArray bezierCurves : curves){ window.draw(bezierCurves); }
		for (ControlPoint cp : arrayOfControlPoints){ 
			cp.drawCircle(); 
			cp.drawText();
		}
		window.display();
	}
}
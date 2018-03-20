#ifndef PROPERTIES
#define PROPERTIES

#define WINDOW_W 800
#define WINDOW_H 600
#define FPS 60

#define PLAYER_H 32
#define PLAYER_W 24

extern const sf::Color COLOR_BG(40, 40, 40);
extern const sf::Color COLOR_PLAYER(255, 240, 255);
extern const sf::Color COLOR_WALL(50, 50, 50);

#define H_ACCEL 10.f/FPS 					//per second
#define H_COEFF 0.3
#define H_OPPOSITE 2.0
#define H_AIR 1.0
#define MIN_H_VEL 0.01						//per frame
#define MAX_H_VEL 200.f/FPS 				//per second

#define GRAVITY 20.f/FPS					//per second
#define V_ACCEL -600.f/FPS					//per second
#define V_HOLD 1
#define V_SAFE 6
#define CUT_V_VEL -20.f/FPS					//per second
#define MAX_V_VEL 400.f/FPS					//per second

#define GAP 0.1

#endif
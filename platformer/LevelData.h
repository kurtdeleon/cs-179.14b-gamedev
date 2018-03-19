#ifndef LEVEL_DATA 
#define LEVEL_DATA

struct LevelData
{
	sf::Vector2f playerPosition;
	std::vector<sf::RectangleShape*> walls;
};

#endif
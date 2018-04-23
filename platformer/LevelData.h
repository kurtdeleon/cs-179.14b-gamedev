#ifndef LEVEL_DATA 
#define LEVEL_DATA

/* Contains data about the level. Data comes from a .txt file. */
struct LevelData
{
	sf::Vector2f playerPosition;
	std::vector<sf::RectangleShape*> walls;
	std::vector<sf::CircleShape*> coins;
	int coinCount;
};

#endif
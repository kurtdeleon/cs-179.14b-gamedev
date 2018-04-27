#ifndef LEVEL_DATA 
#define LEVEL_DATA

/* Contains data about the level. Data comes from a .txt file. */
struct LevelData
{
	sf::RenderWindow *window;
	sf::Vector2f playerPosition;
	std::vector<sf::RectangleShape*> walls;
	std::vector<sf::CircleShape*> coins;
	int coinCounter;
	bool hasWon;

	LevelData( sf::RenderWindow *w )
	{
		window = w;
		coinCounter = 0;
		hasWon = false;
	}

	void PrintEndMessage()
	{
		printf(" __   __                                _\n");
		printf(" \\ \\ / /                               | |\n");
		printf("  \\ V /___  _   _  __      _____  _ __ | |\n");
		printf("   \\ // _ \\| | | | \\ \\ /\\ / / _ \\| \'_ \\| |\n");
		printf("   | | (_) | |_| |  \\ V  V / (_) | | | |_|\n");
		printf("   \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_)\n\n");
		printf("            Thanks for playing.\n");
	}

	void CheckGameStatus()
	{
		if ( coinCounter >= coins.size() )
		{
			hasWon = true;
		}
	}
};

#endif
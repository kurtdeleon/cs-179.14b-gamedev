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

	LevelData( sf::RenderWindow *w )
	{
		window = w;
		coinCounter = 0;
	}

	void CheckGameStatus()
	{
		if ( coinCounter >= coins.size() )
		{
			printf(" __   __                                _\n");
			printf(" \\ \\ / /                               | |\n");
			printf("  \\ V /___  _   _  __      _____  _ __ | |\n");
			printf("   \\ // _ \\| | | | \\ \\ /\\ / / _ \\| \'_ \\| |\n");
			printf("   | | (_) | |_| |  \\ V  V / (_) | | | |_|\n");
			printf("   \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_)\n\n");
			printf("            Thanks for playing.\n");
			window->close();
		}
	}
};

#endif
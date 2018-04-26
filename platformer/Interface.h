#ifndef INTERFACE 
#define INTERFACE

struct Interface
{
	sf::Font font;
	sf::Text currentCoins;
	sf::Text maxCoins;
	int maxC;
	sf::RenderWindow *window;

	Interface( sf::RenderWindow *w, int m )
	{
		window = w;
		maxC = m;

		if (!font.loadFromFile("./resources/game_over.ttf"))
		{
    		window->close();
		}

		currentCoins.setFont(font);
		currentCoins.setCharacterSize(70);
		currentCoins.setFillColor(sf::Color::White);
		maxCoins.setFont(font);
		maxCoins.setCharacterSize(70);
		maxCoins.setFillColor(sf::Color::White);

		maxCoins.setString("Total coins needed: " + std::to_string(maxC) );
	};

	void Update( int score, sf::Vector2f position )
	{
		currentCoins.setString( "Coins: " + std::to_string(score) );
		currentCoins.setPosition(position - sf::Vector2f(370, -200));
		maxCoins.setPosition(position - sf::Vector2f(-100, -200));
	}

	void Draw()
	{
		window->draw( currentCoins );
		window->draw( maxCoins );
	}
};

#endif
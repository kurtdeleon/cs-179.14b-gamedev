#ifndef TEXTURES 
#define TEXTURES

struct Textures
{
	sf::RenderWindow *window;
	sf::Texture tile;
	sf::Texture coin;
	sf::Texture bgTexture;
	sf::Texture playerTexture;

	Textures( sf::RenderWindow *w )
	{
		window = w;

		if( !tile.loadFromFile("./resources/img/tiles.jpg") )
		{
			window->close();
		}
		tile.setSmooth(true);
		tile.setRepeated(true);

		if( !coin.loadFromFile("./resources/img/coins.png") )
		{
			window->close();
		}
		coin.setSmooth(true);

		if ( !bgTexture.loadFromFile("./resources/img/background.png") )
		{
			window->close();
		}

		if( !playerTexture.loadFromFile("./resources/img/idle.gif") )
		{
			window->close();
		}
	};
};

#endif
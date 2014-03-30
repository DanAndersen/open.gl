#include <SFML/Window.hpp>
#include "Common.h"

int main_SFML()
{
	sf::Window window(sf::VideoMode(800, 600), "OpenGL - SFML", sf::Style::Close);

	initGLEW();

	bool running = true;
	while (running)
	{
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::KeyPressed:
				if (windowEvent.key.code == sf::Keyboard::Escape)
				{
					running = false;
				}
				break;
			}
		}

		window.display();
	}

    return 0;
}
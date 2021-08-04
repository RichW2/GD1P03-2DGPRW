#include <SFML/Graphics.hpp>;

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	sf::CircleShape shape2(50);
	shape.setFillColor(sf::Color(250, 255, 255, 255));
	shape2.setFillColor(sf::Color(200, 0, 0, 255));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.display();
	}

	return 0;
}
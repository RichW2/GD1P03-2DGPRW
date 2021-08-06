#include <SFML/Graphics.hpp>;
#include <iostream>;

void InputChecking(sf::RectangleShape &rect, sf::Vector2f &vect) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		vect.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		vect.x = 1;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		vect.y = -1;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		vect.y = 1;

	}
	
	rect.move(vect);
}

int main()
{
	std::vector<sf::Shape*> shapes;

	//player input move vect
	sf::Vector2f moveVector;

	float screenW = 400;
	float screenH = 400;
	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "SFML works!");
	sf::CircleShape shape(100.f);
	sf::CircleShape shape2(50);
	sf::Vector2f shape2Pos = sf::Vector2f(screenW/2, screenH/2); //find center of screen

	shape.setFillColor(sf::Color(150, 105, 255, 255)); //purple circle
	shape.setPosition(shape2Pos);
	shape.setOrigin(shape.getRadius(), shape.getRadius()); //set origin to center of circle
	shapes.push_back(&shape);

	shape2.setFillColor(sf::Color(200, 0, 0, 255)); //red circle
	shape2.setPosition(shape2Pos);
	shape2.setOrigin(shape2.getRadius(), shape2.getRadius());
	shapes.push_back(&shape2);

	sf::RectangleShape rectShape;
	sf::Vector2f rectDim(20, 100);
	rectShape.setSize(rectDim);
	rectShape.setOrigin(rectShape.getSize() / 2.f);
	rectShape.setPosition(shape2Pos);
	rectShape.setFillColor(sf::Color(50, 200, 155, 255));

	shapes.push_back(&rectShape);

	sf::Vector2i mousePos;

	while (window.isOpen())
	{
		moveVector.x = 0; moveVector.y = 0;
		mousePos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				
				if (event.key.code == sf::Keyboard::A) {
					shape.setRadius(shape.getRadius() + 1);
					shape.setOrigin(shape.getRadius(), shape.getRadius());
				}
				if (event.key.code == sf::Keyboard::D) {
					shape.setRadius(shape.getRadius() - 1);
					shape.setOrigin(shape.getRadius(), shape.getRadius());
				}
			}
			
		}
		InputChecking(rectShape, moveVector);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			rectShape.setPosition(sf::Vector2f(mousePos));
		}

		window.clear();
		for (int i = 0; i < shapes.size(); i++) {
			window.draw(*shapes[i]);
		}

		window.display();
	}

	return 0;
}
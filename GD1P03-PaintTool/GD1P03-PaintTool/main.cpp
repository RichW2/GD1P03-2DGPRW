#include <SFML/Graphics.hpp>;
#include <iostream>;
#include "Canvas.h"
#include "Brush.h"

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

sf::RenderWindow* m_renderWindow;
Canvas* m_canvas;
Brush* m_brush;

void Update();
void Render();
sf::Color RandomColour(int cp);

int main()
{
	std::vector<sf::Shape*> shapes;


	//player input move vect
	sf::Vector2f moveVector;

	float screenW = 400;
	float screenH = 400;
	m_renderWindow = new sf::RenderWindow (sf::VideoMode(screenW, screenH), "SFML works!");
	m_canvas = new Canvas(m_renderWindow, screenW, screenH);
	m_brush = new Brush(m_renderWindow, m_canvas);

	

	//sf::CircleShape shape(100.f);
	//sf::Shape* shape2 = new sf::CircleShape(50);
	//m_canvas->AddShape(shape2);
	//
	//sf::Shape* testRect = new sf::RectangleShape(sf::Vector2f(20, 20));
	//testRect->setPosition(50, 100);
	//m_brush->SetShape(testRect);
	//m_canvas->AddShape(m_brush->GetShape());
	//m_canvas->AddShape(testRect);
	// 
	//sf::Vector2f shape2Pos = sf::Vector2f(screenW/2, screenH/2); //find center of screen
	//
	//shape.setFillColor(sf::Color(150, 105, 255, 255)); //purple circle
	//shape.setPosition(shape2Pos);
	//shape.setOrigin(shape.getRadius(), shape.getRadius()); //set origin to center of circle
	//shapes.push_back(&shape);
	//
	//shape2.setFillColor(sf::Color(200, 0, 0, 255)); //red circle
	//shape2.setPosition(shape2Pos);
	//shape2.setOrigin(shape2.getRadius(), shape2.getRadius());
	//shapes.push_back(&shape2);
	//
	//sf::RectangleShape rectShape;
	//sf::Vector2f rectDim(20, 100);
	//rectShape.setSize(rectDim);
	//rectShape.setOrigin(rectShape.getSize() / 2.f);
	//rectShape.setPosition(shape2Pos);
	//rectShape.setFillColor(sf::Color(50, 200, 155, 255));
	//
	//shapes.push_back(&rectShape);
	//
	//sf::Vector2i mousePos;
	//sf::RectangleShape* testRect = new sf::RectangleShape(sf::Vector2f(20, 20));
	//testRect->setFillColor(sf::Color::Blue);
	//testRect->setPosition(m_brush->GetMousePos().x, m_brush->GetMousePos().y);

	Update();

	delete m_renderWindow;
	delete m_canvas;
	delete m_brush;

	return 0;
}

void Update() {
	int cp = 0;
	while (m_renderWindow->isOpen())
	{
		cp++;
		//moveVector.x = 0; moveVector.y = 0;
		//mousePos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (m_renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_renderWindow->close();
			//if (event.type == sf::Event::KeyPressed) {
			//
			//	if (event.key.code == sf::Keyboard::A) {
			//		shape.setRadius(shape.getRadius() + 1);
			//		shape.setOrigin(shape.getRadius(), shape.getRadius());
			//	}
			//	if (event.key.code == sf::Keyboard::D) {
			//		shape.setRadius(shape.getRadius() - 1);
			//		shape.setOrigin(shape.getRadius(), shape.getRadius());
			//	}
			//}

		}
		m_brush->SetMousePos(sf::Mouse::getPosition(*m_renderWindow));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Shape* testRect = new sf::RectangleShape(sf::Vector2f(20, 20));
			m_brush->SetColour(RandomColour(cp));

			testRect->setPosition(m_brush->GetMousePos().x, m_brush->GetMousePos().y);
			m_brush->SetShape(testRect);

			m_canvas->AddShape(m_brush->GetShape());
		}

		Render();
		//InputChecking(rectShape, moveVector);



		//m_renderWindow->clear();
		//for (int i = 0; i < shapes.size(); i++) {
		//	m_renderWindow->draw(*shapes[i]);
		//}
		//
		//m_renderWindow->display();
	}
}

void Render() {
	m_renderWindow->clear();
	m_canvas->Draw();
	//brush draw
	m_renderWindow->display();
}

sf::Color RandomColour(int cp) {
	switch (cp%6) {
	case 0: {
		return sf::Color::Red;
	}
	case 1: {
		return sf::Color::Blue;
	}
	case 2: {
		return sf::Color::Green;
	}
	case 3: {
		return sf::Color::Yellow;
	}
	case 4: {
		return sf::Color::Cyan;
	}
	case 5: {
		return sf::Color::Magenta;
	}
	default: {
		return sf::Color::Red;
	}
	}
}
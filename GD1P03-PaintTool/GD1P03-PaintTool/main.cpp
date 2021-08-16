#include "PaintToolManager.h"



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

sf::RenderWindow* m_toolsWindow;
ToolsCanvas* m_toolsCanvas;

Brush* m_brush;
PaintToolManager mainManager;

//make an image overlaying the whole window
// use the mouse to set pixels of that image


//1: make image
//2: image = size of window
//3: image colour
//4: input method to get mouse position

void Update();
void Render();
sf::Color RandomColour();
void SetupToolbar();

int main()
{
	std::vector<sf::Shape*> shapes;


	//player input move vect
	sf::Vector2f moveVector;

	float screenW = 1000;
	float screenH = 800;
	m_renderWindow = new sf::RenderWindow (sf::VideoMode(screenW, screenH), "SFML works!");
	m_toolsWindow = new sf::RenderWindow(sf::VideoMode(250, 400), "Tools");
	m_canvas = new Canvas(m_renderWindow, screenW, screenH);
	m_toolsCanvas = new ToolsCanvas(m_toolsWindow);
	m_brush = new Brush(m_renderWindow, m_canvas);
	m_brush->SetMode(BRUSHTYPEDRAW);

	SetupToolbar();

	srand(time(NULL));
	Update();

	delete m_renderWindow;
	delete m_toolsWindow;
	delete m_canvas;
	delete m_brush;

	return 0;
}

void Update() {
	while (m_renderWindow->isOpen())
	{
		//if (!m_renderWindow->hasFocus())
			//continue;
			// 
		//moveVector.x = 0; moveVector.y = 0;
		//mousePos = sf::Mouse::getPosition(window);

		sf::Event event;
		
		m_brush->SetMousePos(sf::Mouse::getPosition(*m_toolsWindow));
		while (m_toolsWindow->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {

				m_brush->SetStartHoldMousePos(sf::Mouse::getPosition(*m_toolsWindow));
				//if (event.mouseButton.button == sf::Mouse::Right)

				Button* buttonUnderMouse = m_toolsCanvas->IsMouseOverButton(m_brush->GetStartHoldMousePos());
				if (buttonUnderMouse != nullptr) {
					buttonUnderMouse->UseButton();
				}

			}
		}

		m_brush->SetMousePos(sf::Mouse::getPosition(*m_renderWindow));
		while (m_renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_renderWindow->close();

			if (event.type == sf::Event::MouseButtonPressed) {
				m_brush->SetStartHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
					
				switch (m_brush->GetMode()) {
				case BRUSHTYPEDRAW: {
					break;
				}
				default:
				case BRUSHTYPEBOX: {
					sf::Shape* dummyShape = new sf::RectangleShape(sf::Vector2f(0, 0));
					m_canvas->AddShape(dummyShape);
					break;
				}
				case BRUSHTYPEELLIPSES: {
					sf::Shape* dummyShape = new sf::RectangleShape(sf::Vector2f(0, 0));
					m_canvas->AddShape(dummyShape);
					break;
				}
				case BRUSHTYPELINE: {
					sf::Shape* dummyShape = new sf::RectangleShape(sf::Vector2f(0, 0));
					m_canvas->AddShape(dummyShape);
					break;
				}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				//if (event.mouseButton.button == sf::Mouse::Right) {
				//	m_brush->SetEndHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
				//	m_canvas->AddShape(m_brush->GetShapeWithMode());
				//}
				m_brush->SetEndHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
				switch (m_brush->GetMode()) {
				case BRUSHTYPEDRAW: {
					break;
				}
				default:
				case BRUSHTYPEBOX: {
					m_canvas->PopShape(); //remove dummy shape
					m_canvas->AddShape(m_brush->GetShapeWithMode());
					break;
				}
				case BRUSHTYPEELLIPSES: {
					m_canvas->PopShape();
					m_canvas->AddShape(m_brush->GetShapeWithMode());
					break;
				}
				case BRUSHTYPELINE: {
					m_canvas->PopShape();
					m_canvas->AddShape(m_brush->GetShapeWithMode());
					break;
				}
				}
			}

			if (event.type == sf::Event::Resized) {
				sf::View newView(sf::Vector2f(event.size.width/2, event.size.height/2), sf::Vector2f(event.size.width, event.size.height));
				m_renderWindow->setView(newView);
			}

		}
		

		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//delete most recently created shape
			// create shape

			m_brush->SetColour(RandomColour());
			m_brush->SetEndHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
			
			switch (m_brush->GetMode()) {
			case BRUSHTYPEDRAW: {
				m_brush->m_radius = 2;
				if (m_brush->GetMousePos().x > 0 && m_brush->GetMousePos().y > 0 && m_brush->GetMousePos().x < m_canvas->GetWidth() && m_brush->GetMousePos().y < m_canvas->GetHeight())
					m_canvas->SetPixel(m_brush->GetMousePos().x, m_brush->GetMousePos().y, m_brush->GetColour(), m_brush->m_radius);
				break;
			}
			default:
			case BRUSHTYPEBOX: {
				m_canvas->PopShape();
				m_canvas->AddShape(m_brush->GetShapeWithMode());
				break;
			}
			case BRUSHTYPEELLIPSES: {
				m_canvas->PopShape();
				m_canvas->AddShape(m_brush->GetShapeWithMode());
				break;
			}
			case BRUSHTYPELINE: {
				m_canvas->PopShape();
				m_canvas->AddShape(m_brush->GetShapeWithMode());
				break;
			}
			}


			//sf::Shape* testRect = new sf::RectangleShape(sf::Vector2f(20, 20));
			

			//testRect->setPosition(m_brush->GetMousePos().x, m_brush->GetMousePos().y);
			//m_brush->SetShape(testRect);
			//
			//m_canvas->AddShape(m_brush->GetShape());
			

			//m_renderWindow->setSize(sf::Vector2u(m_renderWindow->getSize().x - 1, m_renderWindow->getSize().y));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			mainManager.OpenPaintDialog(m_brush, m_renderWindow);
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
	//m_toolsWindow->clear();
	m_canvas->Draw();
	m_toolsCanvas->Draw();

	m_renderWindow->display();
	m_toolsWindow->display();
}

sf::Color RandomColour() {
	return sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
}

void SetupToolbar() {
	m_toolsCanvas->AddButton(new Button(10, 10, 30, 30, BUTTONUSE_COLOURPICKER, m_brush, m_canvas));
}


#include "PaintToolManager.h"
#include "Canvas.h"
#include "Brush.h"
#include "ToolsCanvas.h"
#include "Button.h"

sf::RenderWindow* m_renderWindow;
Canvas* m_canvas;

sf::RenderWindow* m_toolsWindow;
ToolsCanvas* m_toolsCanvas;

Brush* m_brush;
PaintToolManager m_manager;

//make an image overlaying the whole window
// use the mouse to set pixels of that image


//1: make image
//2: image = size of window
//3: image colour
//4: input method to get mouse position

void Update();
void Render();
void SetupToolbar();

int main()
{
	std::vector<sf::Shape*> shapes;


	//player input move vect
	sf::Vector2f moveVector;

	float screenW = 1000;
	float screenH = 800;
	m_renderWindow = new sf::RenderWindow (sf::VideoMode(screenW, screenH), "A pretty picture!");
	m_toolsWindow = new sf::RenderWindow(sf::VideoMode(250, 400), "Tools");
	m_toolsWindow->setPosition(sf::Vector2i(m_renderWindow->getPosition().x+m_renderWindow->getSize().x + 3, m_renderWindow->getPosition().y+1));
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

				Button* buttonUnderMouse = m_toolsCanvas->IsMouseOverButton(m_brush->GetStartHoldMousePos());
				if (buttonUnderMouse != nullptr) {
					buttonUnderMouse->UseButton();
					m_toolsCanvas->HighlightButton(buttonUnderMouse);
					if (m_brush->rainbowColourMode) {
						if (buttonUnderMouse->buttonUse == BUTTONUSE_RAINBOWMODE)
							buttonUnderMouse->DimButton(100);
					}
					else {
						if (buttonUnderMouse->buttonUse == BUTTONUSE_RAINBOWMODE)
							buttonUnderMouse->DimButton(0);
					}
				}
				

			}
		}

		m_brush->SetMousePos(sf::Mouse::getPosition(*m_renderWindow));
		while (m_renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //close application
				m_renderWindow->close();

			if (event.type == sf::Event::KeyPressed) { 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { //undo
					m_canvas->UndoShape();
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { //mouse begins hold/clicks once
				m_brush->SetStartHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
					
				switch (m_brush->GetMode()) {
				case BRUSHTYPEDRAW: {
					break;
				}
				case BRUSHTYPEIMAGE: {
					break;
				}
				default:
				case BRUSHTYPEBOX: {
					sf::Shape* dummyShape = new sf::RectangleShape(sf::Vector2f(0, 0)); //create a dummy shape, this is invisible.
					m_canvas->AddShape(dummyShape); //add the invisible shape to the list
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
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { //mouse releases hold
				m_brush->SetEndHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
				switch (m_brush->GetMode()) { 
				case BRUSHTYPEDRAW: { 
					break;
				}
				case BRUSHTYPEIMAGE: {
					break;
				}
				default:
				case BRUSHTYPEBOX: {
					m_canvas->PopShape(); //remove last "ghost" shape
					m_canvas->AddShape(m_brush->GetShapeWithMode()); //add the real shape
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

			if (event.type == sf::Event::Resized) { //stop the canvas from stretching
				sf::View newView(sf::Vector2f(event.size.width/2, event.size.height/2), sf::Vector2f(event.size.width, event.size.height));
				m_renderWindow->setView(newView);
			}

		}
		

		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_renderWindow->hasFocus()) { //mouse button held down
			//delete most recently created shape
			// create shape
			m_brush->SetEndHoldMousePos(sf::Mouse::getPosition(*m_renderWindow));
			
			switch (m_brush->GetMode()) { //this part of the function draws the ghose shapes, or the shapes you see when holding the mouse button
			case BRUSHTYPEDRAW: {
				if (m_brush->GetMousePos().x > 0 && m_brush->GetMousePos().y > 0 && m_brush->GetMousePos().x < m_canvas->GetWidth() && m_brush->GetMousePos().y < m_canvas->GetHeight()) //are we on the canvas?
					m_canvas->SetPixel(m_brush->GetMousePos().x, m_brush->GetMousePos().y, m_brush->GetColour(), m_brush->GetRadius()); //set the pixels in an area
				break;
			}
			case BRUSHTYPEIMAGE: {
				if (m_brush->GetMousePos().x > 0 && m_brush->GetMousePos().y > 0 && m_brush->GetMousePos().x < m_canvas->GetWidth() && m_brush->GetMousePos().y < m_canvas->GetHeight())
					m_canvas->SetPixel(m_brush->GetMousePos().x, m_brush->GetMousePos().y, m_brush->GetColour(), m_brush->m_bitmapImg); 
				break;
			}
			default:
			case BRUSHTYPEBOX: {
				m_canvas->PopShape(); //remove the dummy or last shape created
				m_canvas->AddShape(m_brush->GetShapeWithMode()); //add a new shape (that will very quickly be removed by line above)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_renderWindow->hasFocus()) {
			m_manager.OpenPaintDialog(m_brush, m_renderWindow); //alternate way to open colour picker
		}

		Render();
		//InputChecking(rectShape, moveVector);
	}
}

void Render() {
	//m_toolsWindow->clear();
	m_canvas->Draw(); //draw the picture
	m_toolsCanvas->Draw(); //draw the buttons and toolbar

	m_renderWindow->display(); //show them
	m_toolsWindow->display();
}



void SetupToolbar() {
	//this function sets up the toolbar layout.
	m_toolsCanvas->AddButton(new Button(10, 10, 30, 30, BUTTONUSE_COLOURPICKER, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/ColourPicker.png");

	m_toolsCanvas->AddButton(new Button(50, 10, 30, 30, BUTTONUSE_RAINBOWMODE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/RainbowMode.png");

	m_toolsCanvas->AddButton(new Button(90, 10, 30, 30, BUTTONUSE_BRUSHBIGGER, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushIncrease.png");

	m_toolsCanvas->AddButton(new Button(130, 10, 30, 30, BUTTONUSE_BRUSHSMALLER, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushDecrease.png");

	m_toolsCanvas->AddButton(new Button(10, 50, 30, 30, BUTTONUSE_BRUSHDRAW, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushDraw.png");
	m_toolsCanvas->AddButton(new Button(50, 50, 30, 30, BUTTONUSE_BRUSHBOX, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushBox.png");
	m_toolsCanvas->AddButton(new Button(90, 50, 30, 30, BUTTONUSE_BRUSHLINE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushLine.png");
	m_toolsCanvas->AddButton(new Button(130, 50, 30, 30, BUTTONUSE_BRUSHELLIPSE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushCircle.png");

	m_toolsCanvas->AddButton(new Button(10, 90, 30, 30, BUTTONUSE_FILLBACKGROUD, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/CanvasClear.png");
	m_toolsCanvas->AddButton(new Button(50, 90, 30, 30, BUTTONUSE_UNDO, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/Undo.png");
	m_toolsCanvas->AddButton(new Button(90, 90, 30, 30, BUTTONUSE_SAVEIMAGE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/SaveIcon.png");
	m_toolsCanvas->AddButton(new Button(130, 90, 30, 30, BUTTONUSE_LOADIMAGE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/LoadIcon.png");

	m_toolsCanvas->AddButton(new Button(10, 130, 30, 30, BUTTONUSE_BRUSHPOLYGON, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/BrushPolygon.png");
	m_toolsCanvas->AddButton(new Button(50, 130, 30, 30, BUTTONUSE_POLYGONINCREASE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/PolygonIncrease.png");
	m_toolsCanvas->AddButton(new Button(90, 130, 30, 30, BUTTONUSE_POLYGONDECREASE, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/PolygonDecrease.png");
	m_toolsCanvas->AddButton(new Button(130, 130, 30, 30, BUTTONUSE_STAR, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/Star.png");
	m_toolsCanvas->AddButton(new Button(170, 130, 30, 30, BUTTONUSE_HEART, m_brush, m_canvas, &m_manager));
	m_toolsCanvas->GetLastButton()->AddIcon("Icons/Heart.png");
}


#include "Button.h"

Button::Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse, Brush* _brush, Canvas* _canvas)
{
	buttonShape = sf::RectangleShape();
	buttonPos = sf::Vector2f(xPos, yPos);
	buttonSize = sf::Vector2f(xSiz, ySiz);
	buttonShape.setPosition(buttonPos);
	buttonShape.setSize(buttonSize);
	buttonUse = _buttonUse;
	//m_paintManager = _paintManage;
	m_brush = _brush;
	m_canvas = _canvas;
}

void Button::UseButton()
{
	switch (buttonUse) {
	default:
	case BUTTONUSE_COLOURPICKER: {
		//m_paintManager->OpenPaintDialog();
		std::cout << "Button works";
		break;
	}
	}
}

void Button::DisplayButton(sf::RenderWindow* toolWindow)
{
	toolWindow->draw(buttonShape);
}


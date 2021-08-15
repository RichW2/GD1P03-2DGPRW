#include "Button.h"

Button::Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse)
{
	buttonShape = sf::RectangleShape();
	buttonPos = sf::Vector2f(xPos, yPos);
	buttonSize = sf::Vector2f(xSiz, ySiz);
	buttonShape.setPosition(buttonPos);
	buttonShape.setSize(buttonSize);
	buttonUse = _buttonUse;
}

void Button::UseButton()
{
	switch (buttonUse) {
	default:
	case BUTTONUSE_COLOURPICKER: {
		break;
	}
	}
}

void Button::DisplayButton(sf::RenderWindow* toolWindow)
{
	toolWindow->draw(buttonShape);
}

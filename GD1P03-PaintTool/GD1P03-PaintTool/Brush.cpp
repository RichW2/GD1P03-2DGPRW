#include "Brush.h"

Brush::Brush(sf::RenderWindow* _window, Canvas* _canvas)
{
	m_rendWindow = _window;
	m_canvas = _canvas;
	m_brushMode = BRUSHTYPEBOX;
}


void Brush::SetMousePos(sf::Vector2i pos)
{
	m_mousePos = pos;
}
sf::Vector2i Brush::GetMousePos()
{
	return m_mousePos;
}

void Brush::SetStartHoldMousePos(sf::Vector2i pos)
{
	m_startMouseHoldPos = pos;
}
sf::Vector2i Brush::GetStartHoldMousePos()
{
	return m_startMouseHoldPos;
}

void Brush::SetEndHoldMousePos(sf::Vector2i pos)
{
	m_endMouseHoldPos = pos;
}

sf::Vector2i Brush::GetEndHoldMousePos()
{
	return m_endMouseHoldPos;
}


sf::Shape* Brush::GetShape()
{
	m_selectedShape->setFillColor(m_brushColour);
	return m_selectedShape;
}
void Brush::SetShape(sf::Shape* _shape)
{
	m_selectedShape = _shape;
}


sf::Shape* Brush::GetNewShape()
{
	return nullptr;
}

void Brush::SetMode(EBRUSHTYPE _type)
{
	m_brushMode = _type;
}

sf::Shape* Brush::GetShapeWithMode()
{
	switch (m_brushMode) {
	case BRUSHTYPEBOX:{
		int xSize = abs(this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x);
		int ySize = abs(this->GetEndHoldMousePos().y - this->GetStartHoldMousePos().y);
		int xPo = this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x;
		int yPo = this->GetEndHoldMousePos().y - this->GetStartHoldMousePos().y;
		sf::Vector2f recSize = sf::Vector2f(xSize, ySize);
		sf::Shape* newRect = new sf::RectangleShape(recSize);
		//newRect->setOrigin(recSize.x/2, recSize.y/2);
		newRect->setPosition(this->GetStartHoldMousePos().x + xPo, this->GetStartHoldMousePos().y + yPo);
		newRect->setOutlineColor(this->GetColour());
		newRect->setOutlineThickness(5);
		newRect->setFillColor(sf::Color::Transparent);
		return newRect;
	}
	default: {

	}
	}
}


sf::Color Brush::GetColour()
{
	return m_brushColour;
}
void Brush::SetColour(sf::Color _colour)
{
	m_brushColour = _colour;
}



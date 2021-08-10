#include "Brush.h"

Brush::Brush(sf::RenderWindow* _window, Canvas* _canvas)
{
	m_rendWindow = _window;
	m_canvas = _canvas;
	m_brushType = BRUSHTYPEBOX;
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


sf::Color Brush::GetColour()
{
	return m_brushColour;
}
void Brush::SetColour(sf::Color _colour)
{
	m_brushColour = _colour;
}



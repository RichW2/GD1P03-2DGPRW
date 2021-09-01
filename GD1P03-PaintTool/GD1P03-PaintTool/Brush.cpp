#include "Brush.h"

float GetAngle2Points(float _x1, float _y1, float _x2, float _y2) {
	float angle;
	float pi = 3.14159;
	angle = atan2(_y2 - _y1, _x2 - _x1) * (180/pi);
	return angle;
}

float GetAngle2Lines(float _x, float _y) {
	float angle;
	float pi = 3.14159;
	angle = atan2(_y, _x) * (180 / pi);
	return angle;
}

float PythagLines(float _x, float _y) {
	return sqrtf(_x * _x + _y * _y);
}

Brush::Brush(sf::RenderWindow* _window, Canvas* _canvas)
{
	m_rendWindow = _window;
	m_canvas = _canvas;
	m_brushMode = BRUSHTYPEBOX;
	m_radius = 2;
	m_polygonSides = 5;
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

EBRUSHTYPE Brush::GetMode()
{
	return m_brushMode;
}

sf::Shape* Brush::GetShapeWithMode()
{
	int xSize = abs(this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x);
	int ySize = abs(this->GetEndHoldMousePos().y - this->GetStartHoldMousePos().y);
	int xSizeN = this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x;
	int ySizeN = this->GetEndHoldMousePos().y - this->GetStartHoldMousePos().y;
	int xPo = (this->GetEndHoldMousePos().x + this->GetStartHoldMousePos().x) / 2;
	int yPo = (this->GetEndHoldMousePos().y + this->GetStartHoldMousePos().y) / 2;

	switch (m_brushMode) {
	default:
	case BRUSHTYPEBOX:{
		
		sf::Vector2f recSize = sf::Vector2f(xSize, ySize);
		sf::Shape* newRect = new sf::RectangleShape(recSize);
		newRect->setOrigin(recSize.x/2, recSize.y/2);
		newRect->setPosition(xPo, yPo);
		newRect->setOutlineColor(this->GetColour());
		newRect->setOutlineThickness(this->m_radius);
		newRect->setFillColor(sf::Color::Transparent);
		return newRect;
	}
	case BRUSHTYPEELLIPSES: {
		sf::Vector2f shapeSiz = sf::Vector2f(xSize, ySize);
		float rad = ySizeN / 2;
		sf::Shape* newElip = new sf::CircleShape(rad);
		
		float xScal = (this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x)/rad/2;
		float yScal = 1;
		newElip->setScale(xScal, yScal);

		//newElip->setOrigin(shapeSiz.x / 2, shapeSiz.y / 2);
		newElip->setPosition(this->GetStartHoldMousePos().x, this->GetStartHoldMousePos().y);
		newElip->setOutlineColor(this->GetColour());
		newElip->setOutlineThickness(this->m_radius);
		newElip->setFillColor(sf::Color::Transparent);
		return newElip;
	}
	case BRUSHTYPELINE: {
		sf::Vector2f recSize = sf::Vector2f(PythagLines(xSize, ySize), m_radius);
		sf::Shape* newRect = new sf::RectangleShape(recSize);
		float angle= GetAngle2Lines(xSizeN, ySizeN);
		newRect->setOrigin(recSize.x / 2, recSize.y / 2);
		newRect->setPosition(xPo, yPo);
		newRect->rotate(angle);
		newRect->setOutlineColor(this->GetColour());
		newRect->setOutlineThickness(0);
		newRect->setFillColor(this->GetColour());
		return newRect;
	}
	case BRUSHTYPEPOLYGON: {
		sf::Vector2f shapeSiz = sf::Vector2f(xSize, ySize);
		float rad = ySizeN / 2;
		sf::Shape* newElip = new sf::CircleShape(rad);

		float xScal = (this->GetEndHoldMousePos().x - this->GetStartHoldMousePos().x) / rad / 2;
		float yScal = 1;
		newElip->setScale(xScal, yScal);
		dynamic_cast<sf::CircleShape*>(newElip)->setPointCount(this->GetPolySides());

		newElip->setPosition(this->GetStartHoldMousePos().x, this->GetStartHoldMousePos().y);
		newElip->setOutlineColor(this->GetColour());
		newElip->setOutlineThickness(this->m_radius);
		newElip->setFillColor(sf::Color::Transparent);
		return newElip;
	}
	}
}

void Brush::IncreaseRadius(int val)
{
	m_radius += val;
	if (m_radius < 2)
		m_radius = 2;
	if (m_radius > 20)
		m_radius = 20;
}

int Brush::GetRadius()
{
	return m_radius;
}

void Brush::IncreasePolySides(int val)
{
	m_polygonSides += val;
	if (m_polygonSides > 20)
		m_polygonSides = 20;
	if (m_polygonSides < 3)
		m_polygonSides = 3;
}

int Brush::GetPolySides()
{
	return m_polygonSides;
}


sf::Color Brush::GetColour()
{
	if (rainbowColourMode)
		return RandomColour();
	return m_brushColour;
}
void Brush::SetColour(sf::Color _colour)
{
	m_brushColour = _colour;
}
sf::Color Brush::RandomColour()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
}


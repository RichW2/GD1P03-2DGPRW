#pragma once
#include "Canvas.h"

enum EBRUSHTYPE {
	BRUSHTYPEDRAW,
	BRUSHTYPEBOX,
	BRUSHTYPELINE,
	BRUSHTYPEELLIPSES,
};

class Brush
{
private:
	int m_xPos, m_yPos;
	sf::Vector2i m_mousePos;
	sf::Vector2i m_startMouseHoldPos;
	sf::Vector2i m_endMouseHoldPos;
	sf::RenderWindow* m_rendWindow;
	Canvas* m_canvas;
	sf::Shape* m_selectedShape;
	sf::Color m_brushColour;
	EBRUSHTYPE m_brushMode;

public:
	int m_radius;
	Brush(sf::RenderWindow* _window, Canvas* _canvas);

	void SetMousePos(sf::Vector2i pos);
	sf::Vector2i GetMousePos();

	void SetStartHoldMousePos(sf::Vector2i pos);
	sf::Vector2i GetStartHoldMousePos();

	void SetEndHoldMousePos(sf::Vector2i pos);
	sf::Vector2i GetEndHoldMousePos();

	sf::Shape* GetShape();
	void SetShape(sf::Shape* _shape);
	sf::Shape* GetNewShape();

	void SetMode(EBRUSHTYPE _type);
	sf::Shape* GetShapeWithMode();

	sf::Color GetColour();
	void SetColour(sf::Color _colour);

};


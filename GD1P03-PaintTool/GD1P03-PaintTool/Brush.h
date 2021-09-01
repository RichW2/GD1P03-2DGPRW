#pragma once
#include "Canvas.h"

enum EBRUSHTYPE {
	BRUSHTYPEDRAW,
	BRUSHTYPEBOX,
	BRUSHTYPELINE,
	BRUSHTYPEELLIPSES,
	BRUSHTYPEPOLYGON,
	BRUSHTYPEIMAGE
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
	int m_radius;
	int m_polygonSides;

public:
	bool rainbowColourMode;
	sf::Image m_bitmapImg;
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
	EBRUSHTYPE GetMode();
	sf::Shape* GetShapeWithMode();

	void IncreaseRadius(int val);
	int GetRadius();

	void IncreasePolySides(int val);
	int GetPolySides();

	sf::Color GetColour();
	void SetColour(sf::Color _colour);
	sf::Color RandomColour();

};


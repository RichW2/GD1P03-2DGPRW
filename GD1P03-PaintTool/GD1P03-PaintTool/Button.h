#pragma once
#include <SFML/Graphics.hpp>;
#include <string>
#include "Brush.h"
#include "Canvas.h"
#include <iostream>
//#include "PaintToolManager.h"

enum EBUTTONUSE {
	BUTTONUSE_BRUSHBIGGER,
	BUTTONUSE_BRUSHSMALLER,
	BUTTONUSE_COLOURPICKER
};

class Button
{
public:
	Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse, Brush* _brush, Canvas* _canvas);

	void UseButton();

	void DisplayButton(sf::RenderWindow* toolWindow);

	EBUTTONUSE buttonUse;
	std::string buttonText;
	sf::Color buttonColour;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	sf::RectangleShape buttonShape;
	//PaintToolManager* m_paintManager;
	Brush* m_brush;
	Canvas* m_canvas;
};


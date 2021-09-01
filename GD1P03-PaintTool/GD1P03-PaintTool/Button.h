#pragma once
#include <SFML/Graphics.hpp>;
#include <string>
#include "Brush.h"
#include "Canvas.h"
#include <iostream>
#include "PaintToolManager.h"

enum EBUTTONUSE {
	BUTTONUSE_BRUSHBIGGER,
	BUTTONUSE_BRUSHSMALLER,
	BUTTONUSE_COLOURPICKER,
	BUTTONUSE_BRUSHBOX,
	BUTTONUSE_BRUSHLINE,
	BUTTONUSE_BRUSHDRAW,
	BUTTONUSE_BRUSHPOLYGON,
	BUTTONUSE_BRUSHELLIPSE,
	BUTTONUSE_RAINBOWMODE,
	BUTTONUSE_FILLBACKGROUD,
	BUTTONUSE_POLYGONINCREASE,
	BUTTONUSE_POLYGONDECREASE,
	BUTTONUSE_UNDO,
	BUTTONUSE_SAVEIMAGE,
	BUTTONUSE_LOADIMAGE,
	BUTTONUSE_STAR,
	BUTTONUSE_HEART
};

class Button
{
public:
	Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse, Brush* _brush, Canvas* _canvas, PaintToolManager* _manager);

	void UseButton();

	void DisplayButton(sf::RenderWindow* toolWindow);
	void DimButton(int amount);

	void AddIcon(std::string imagePath);

	EBUTTONUSE buttonUse;

	sf::Image buttonIconImg;
	sf::Texture buttonIconTex;
	sf::Sprite buttonIconSpr;

	std::string buttonText;
	sf::Color buttonColour;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	sf::RectangleShape buttonShape;
	//PaintToolManager* m_paintManager;
	Brush* m_brush;
	Canvas* m_canvas;
	PaintToolManager* m_manager;
};


#pragma once
#include <SFML/Graphics.hpp>;
#include <string>

enum EBUTTONUSE {
	BUTTONUSE_BRUSHBIGGER,
	BUTTONUSE_BRUSHSMALLER,
	BUTTONUSE_COLOURPICKER
};

class Button
{
public:
	Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse);

	void UseButton();

	void DisplayButton(sf::RenderWindow* toolWindow);

	EBUTTONUSE buttonUse;
	std::string buttonText;
	sf::Color buttonColour;
	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	sf::RectangleShape buttonShape;
};


#pragma once
#include <SFML/Graphics.hpp>;
#include "Button.h"


class ToolsCanvas
{
public:
	sf::RenderWindow* m_toolsWindow;
	ToolsCanvas(sf::RenderWindow* _window);

	std::vector<Button*> allButtons;

	void AddButton(Button* newButton);

	Button* IsMouseOverButton(sf::Vector2i mousePos);

	void Draw();
};


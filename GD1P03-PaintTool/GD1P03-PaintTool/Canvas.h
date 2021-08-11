#pragma once
#include <SFML/Graphics.hpp>;
#include <list>

class Canvas
{
private:
	//std::list<sf::Shape*> m_shapes;
	std::vector<sf::Shape*> m_shapes;
	sf::RenderWindow* m_rendWindow;
	sf::RectangleShape m_background;
	sf::Image m_bgImage;
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	int m_width = 400;
	int m_height = 400;

public:
	Canvas(sf::RenderWindow* _window, int _width, int _height);

	void SetWidth(int newVal);
	void SetHeight(int newVal);
	int GetWidth();
	int GetHeight();

	void SetPixel(int x, int y, sf::Color col, int rad);
	void AddShape(sf::Shape* newShape);

	void Draw();


	
};


#include "Canvas.h"
#include <SFML/Graphics.hpp>;


//Canvas::Canvas(int _width, int _height)
//{
//	
//	//sf::RenderWindow m_Window(sf::VideoMode(m_width, m_height), "A basic canvas");
//}

Canvas::Canvas(sf::RenderWindow* _window, int _width, int _height)
{
	SetWidth(_width);
	SetHeight(_height);
	m_rendWindow = _window;
	sf::Vector2f bgSize = sf::Vector2f(_width, _height);
	m_background.setSize(bgSize);
	m_background.setFillColor(sf::Color(255, 255, 255, 100));
}

void Canvas::SetWidth(int newVal)
{
	m_width = newVal;
}

void Canvas::SetHeight(int newVal)
{
	m_height = newVal;
}

int Canvas::GetWidth()
{
	return m_width;
}

int Canvas::GetHeight()
{
	return m_height;
}

void Canvas::AddShape(sf::Shape* newShape)
{
	m_shapes.push_back(newShape);
}

void Canvas::Draw()
{
	m_rendWindow->clear();
	m_rendWindow->draw(m_background);
	for (int i = 0; i < m_shapes.size(); i++) {
		m_rendWindow->draw(*m_shapes[i]);
	}
}

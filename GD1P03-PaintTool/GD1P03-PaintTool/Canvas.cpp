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

	m_bgImage.create(_width, _height, sf::Color(255, 255, 255, 100));
	m_bgTexture.loadFromImage(m_bgImage);
	m_bgSprite.setTexture(m_bgTexture);
	//m_bgSprite.setOrigin(_width / 2, _height / 2);

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

void Canvas::SetPixel(int x, int y, sf::Color col, int rad)
{
	for (int i = -rad/2; i < rad/2; i++) {
		for (int j = -rad/2; j < rad/2; j++) {

			m_bgImage.setPixel(x + i, y+j, col);
		}
		

	}
	
}

void Canvas::AddShape(sf::Shape* newShape)
{
	m_shapes.push_back(newShape);
}

void Canvas::PopShape()
{
	delete m_shapes.back(); //remove last shape from memory
	m_shapes.pop_back(); //remove last position
}

void Canvas::AddNewImage()
{
	m_bgImage.create(GetHeight(), GetHeight(), sf::Color(255, 255, 255, 0));
	m_bgTexture.loadFromImage(m_bgImage);
	m_bgSprite.setTexture(m_bgTexture);
}

void Canvas::ResizeBGImage(int newX, int newY)
{

}

void Canvas::Draw()
{
	m_rendWindow->clear();
	//m_rendWindow->draw(m_background);
	m_bgTexture.loadFromImage(m_bgImage);
	m_rendWindow->draw(m_bgSprite);
	for (int i = 0; i < m_shapes.size(); i++) {
		m_rendWindow->draw(*m_shapes[i]);
	}
}

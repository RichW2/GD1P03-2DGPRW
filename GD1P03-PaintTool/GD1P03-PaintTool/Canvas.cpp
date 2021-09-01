#include "Canvas.h"
#include <iostream>

Canvas::Canvas(sf::RenderWindow* _window, int _width, int _height)
{
	SetWidth(_width);
	SetHeight(_height);
	m_rendWindow = _window;
	sf::Vector2f bgSize = sf::Vector2f(_width, _height);

	m_bgImage.create(_width, _height, sf::Color(255, 255, 255, 255));
	m_bgTexture.loadFromImage(m_bgImage);
	m_bgSprite.setTexture(m_bgTexture);
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

sf::RenderWindow* Canvas::GetRenderWindow()
{
	return m_rendWindow;
}

void Canvas::ResetImageColour(sf::Color newCol)
{
}

void Canvas::SetPixel(int x, int y, sf::Color col, int rad)
{
	for (int i = -rad/2; i < rad/2; i++) {
		for (int j = -rad/2; j < rad/2; j++) {
			if (y + j <= 0 || y + j >= m_bgImage.getSize().y || x + i <= 0 || x + i >= m_bgImage.getSize().x) //are we drawing off the image?
				continue;
			m_bgImage.setPixel(x + i, y+j, col);
		}
	}
}

void Canvas::SetPixel(int x, int y, sf::Color col, sf::Image img)
{
	int xS = img.getSize().x;
	int yS = img.getSize().y;
	for (int i = 0; i < yS; i++) {
		for (int j = 0; j < xS; j++) {
			if (y + j <= 0 || y + j >= m_bgImage.getSize().y || x + i <= 0 || x + i >= m_bgImage.getSize().x) //are we drawing off the image?
				continue;
			if (img.getPixel(i,j) == sf::Color::Black)
				m_bgImage.setPixel(x + i, y + j, col);
		}
	}
}

void Canvas::AddShape(sf::Shape* newShape)
{
	//m_rendWindow->draw(*newShape);
	//m_bgTexture.update(*m_rendWindow);
	m_shapes.push_back(newShape);
}

void Canvas::PopShape()
{
	if (m_shapes.size() != 0) {
		delete m_shapes.back(); //remove last shape from memory
		m_shapes.pop_back(); //remove last position
	}
}

void Canvas::UndoShape()
{
	PopShape();
}

void Canvas::AddNewImage(sf::Color newCol)
{
	m_bgImage.create(m_bgImage.getSize().x, m_bgImage.getSize().y, newCol);
	m_bgTexture.loadFromImage(m_bgImage);
	m_bgSprite.setTexture(m_bgTexture);
}

sf::Image* Canvas::GetImage()
{
	return &m_bgImage;
}

sf::Texture* Canvas::GetTexture()
{
	return &m_bgTexture;
}

sf::Sprite* Canvas::GetSprite()
{
	return &m_bgSprite;
}

void Canvas::ResizeBGImage(int newX, int newY)
{
	
}

void Canvas::Draw()
{
	m_rendWindow->clear();
	//m_rendWindow->draw(m_background);
	//m_bgTexture.loadFromImage(m_bgImage);
	m_bgTexture.create(m_bgImage.getSize().x, m_bgImage.getSize().y);
	m_bgTexture.update(m_bgImage);
	m_rendWindow->draw(m_bgSprite);
	for (int i = 0; i < m_shapes.size(); i++) {
		m_rendWindow->draw(*m_shapes[i]);
	}
	//m_bgTexture.update(*m_rendWindow);
	//m_rendWindow->clear();
	//m_rendWindow->draw(m_bgSprite);
}

void Canvas::Save(const std::string& filename)
{
	sf::Texture texture;
	texture.create(m_rendWindow->getSize().x, m_rendWindow->getSize().y);
	texture.update(*m_rendWindow);
	if (texture.copyToImage().saveToFile(filename))
	{
		std::cout << "screenshot saved to " << filename << std::endl;
	}
	else {
		std::cout << "failed to save image \(and the developer is sad\)\n";
	}
}

void Canvas::Load()
{
	m_bgImage.loadFromFile("Saves/loadthis.png");
}

#pragma once
#include <SFML/Graphics.hpp>;

class Canvas
{
private:
	//std::list<sf::Shape*> m_shapes;
	std::vector<sf::Shape*> m_shapes;
	sf::RenderWindow* m_rendWindow;
	sf::Image m_bgImage;
	sf::Image* m_currentBGImage;
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

	sf::RenderWindow* GetRenderWindow();
	void ResetImageColour(sf::Color newCol);

	void SetPixel(int x, int y, sf::Color col, int rad);
	void SetPixel(int x, int y, sf::Color col, sf::Image img);
	void AddShape(sf::Shape* newShape);
	void PopShape();
	void UndoShape();
	void AddNewImage(sf::Color newCol);
	sf::Image* GetImage();
	sf::Texture* GetTexture();
	sf::Sprite* GetSprite();
	void ResizeBGImage(int newX, int newY);

	void Draw();

	void Save(const std::string& filename);
	void Load();
	
};


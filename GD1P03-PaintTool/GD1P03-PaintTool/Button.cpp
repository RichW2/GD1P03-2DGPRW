#include "Button.h"

Button::Button(int xPos, int yPos, float xSiz, float ySiz, EBUTTONUSE _buttonUse, Brush* _brush, Canvas* _canvas, PaintToolManager* _manager)
{
	buttonShape = sf::RectangleShape();
	buttonPos = sf::Vector2f(xPos, yPos);
	buttonSize = sf::Vector2f(xSiz, ySiz);
	buttonShape.setPosition(buttonPos);
	buttonShape.setSize(buttonSize);
	buttonUse = _buttonUse;
	//m_paintManager = _paintManage;
	m_brush = _brush;
	m_canvas = _canvas;
	m_manager = _manager;
}

void Button::UseButton()
{
	switch (buttonUse) {
	default:
	case BUTTONUSE_COLOURPICKER: {
		m_manager->OpenPaintDialog(m_brush, m_canvas->GetRenderWindow());
		break;
	}
	case BUTTONUSE_BRUSHBIGGER: {
		m_brush->IncreaseRadius(1);
		std::cout << m_brush->GetRadius() << "\n";
		break;
	}
	case BUTTONUSE_BRUSHSMALLER: {
		m_brush->IncreaseRadius(-1);
		std::cout << m_brush->GetRadius() << "\n";
		break;
	}
	case BUTTONUSE_BRUSHDRAW:{
		m_brush->SetMode(BRUSHTYPEDRAW);
		break;
	}
	case BUTTONUSE_BRUSHBOX: {
		m_brush->SetMode(BRUSHTYPEBOX);
		break;
	}
	case BUTTONUSE_BRUSHLINE: {
		m_brush->SetMode(BRUSHTYPELINE);
		break;
	}
	case BUTTONUSE_BRUSHELLIPSE: {
		m_brush->SetMode(BRUSHTYPEELLIPSES);
		break;
	}
	case BUTTONUSE_BRUSHPOLYGON: {
		m_brush->SetMode(BRUSHTYPEPOLYGON);
		break;
	}
	case BUTTONUSE_RAINBOWMODE: {
		m_brush->rainbowColourMode = !m_brush->rainbowColourMode;
		break;
	}
	case BUTTONUSE_FILLBACKGROUD: {
		m_canvas->AddNewImage(m_brush->GetColour());
		break;
	}
	case BUTTONUSE_POLYGONINCREASE: {
		m_brush->IncreasePolySides(1);
		break;
	}
	case BUTTONUSE_POLYGONDECREASE: {
		m_brush->IncreasePolySides(-1);
		break;
	}
	case BUTTONUSE_UNDO: {
		m_canvas->UndoShape();
		break;
	}
	case BUTTONUSE_SAVEIMAGE: {

		m_canvas->Save("Saves\\SavedImage.png");
		break;
	}
	case BUTTONUSE_LOADIMAGE : {

		m_canvas->Load();
		break;
	}
	case BUTTONUSE_STAR: {
		m_brush->SetMode(BRUSHTYPEIMAGE);
		m_brush->m_bitmapImg.loadFromFile("Icons/Star.png");
		break;
	}
	case BUTTONUSE_HEART: {
		m_brush->SetMode(BRUSHTYPEIMAGE);
		m_brush->m_bitmapImg.loadFromFile("Icons/Heart.png");
		break;
	}
	}
}

void Button::DisplayButton(sf::RenderWindow* toolWindow)
{
	toolWindow->draw(buttonShape);
	toolWindow->draw(buttonIconSpr);
}

void Button::DimButton(int amount)
{
	buttonIconSpr.setColor(sf::Color(255 - amount, 255 - amount, 255 - amount, 255));
}

void Button::AddIcon(std::string imagePath)
{
	sf::Image newImage;
	newImage.loadFromFile(imagePath);
	buttonIconTex.loadFromImage(newImage);
	buttonIconSpr.setTexture(buttonIconTex);
	buttonIconSpr.setScale(buttonSize.x/buttonIconTex.getSize().x, buttonSize.y/ buttonIconTex.getSize().y);
	buttonIconSpr.setPosition(buttonPos.x, buttonPos.y);
}


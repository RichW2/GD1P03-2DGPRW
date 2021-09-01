#include "ToolsCanvas.h"

ToolsCanvas::ToolsCanvas(sf::RenderWindow* _window)
{
	m_toolsWindow = _window;
}

void ToolsCanvas::AddButton(Button* newButton)
{
	allButtons.push_back(newButton);
}

Button* ToolsCanvas::IsMouseOverButton(sf::Vector2i mp)
{
	for (int i = 0; i < allButtons.size(); i++) {
		Button* currButton = allButtons[i];
		if (mp.x > currButton->buttonPos.x && mp.x < currButton->buttonPos.x + currButton->buttonSize.x) {
			if (mp.y > currButton->buttonPos.y && mp.y < currButton->buttonPos.y + currButton->buttonSize.y) {
				return currButton;
			}
		}
	}
	return nullptr;
}

void ToolsCanvas::HighlightButton(Button* theButton)
{
	if (theButton->buttonUse == BUTTONUSE_BRUSHBOX || theButton->buttonUse == BUTTONUSE_BRUSHDRAW || theButton->buttonUse == BUTTONUSE_BRUSHELLIPSE || theButton->buttonUse == BUTTONUSE_BRUSHLINE || theButton->buttonUse == BUTTONUSE_BRUSHPOLYGON || theButton->buttonUse == BUTTONUSE_STAR || theButton->buttonUse == BUTTONUSE_HEART)
	{ //unhilights all other drawmode buttons
		for (int i = 0; i < allButtons.size(); i++) {
			if (allButtons[i]->buttonUse != BUTTONUSE_RAINBOWMODE)
				allButtons[i]->DimButton(0);
		}
		theButton->DimButton(100);
	}
}

Button* ToolsCanvas::GetLastButton()
{
	return allButtons.back();
}

void ToolsCanvas::Draw()
{
	m_toolsWindow->clear(sf::Color(200, 200, 200,255)); //set the tool canvas background to a nice grey colour
	for (int i = 0; i < allButtons.size(); i++) {
		allButtons[i]->DisplayButton(m_toolsWindow); //show all buttons 
	}
}
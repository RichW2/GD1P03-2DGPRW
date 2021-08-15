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

void ToolsCanvas::Draw()
{
	m_toolsWindow->clear();
	for (int i = 0; i < allButtons.size(); i++) {
		allButtons[i]->DisplayButton(m_toolsWindow);
	}
}
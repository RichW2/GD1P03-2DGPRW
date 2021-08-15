#pragma once
#include <SFML/Graphics.hpp>;
#include <iostream>;
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <wingdi.h> //required for colour handler
#include "Canvas.h"
#include "Brush.h"
#include "Button.h"
#include "ToolsCanvas.h"

class PaintToolManager
{
private:

public:
	CHOOSECOLOR cc; //custom colour box
	COLORREF acrCustClr[16]; //array of custom colours
	HWND hwnd; //handle to window
	//HBRUSH hrush;
	DWORD rgbCurrent; //iniciant color selection the value returned when colour is picked.
	COLORREF cr;

	bool isPaintDialogOpen = false;

	PaintToolManager();
	~PaintToolManager();
	void OpenPaintDialog(Brush* _brush, sf::Window* _window);
	
};


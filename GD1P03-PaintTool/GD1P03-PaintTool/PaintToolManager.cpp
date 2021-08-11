#include "PaintToolManager.h"


PaintToolManager::PaintToolManager()
{
}

PaintToolManager::~PaintToolManager()
{
}

void PaintToolManager::OpenPaintDialog(Brush* _brush, sf::Window* _window)
{
	hwnd = _window->getSystemHandle();

	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN;

	if (ChooseColor(&cc) == TRUE) {
		cr = cc.rgbResult;
		sf::Color tmpCol;
		tmpCol.r = GetRValue(cr);
		tmpCol.g = GetGValue(cr);
		tmpCol.b = GetBValue(cr);

		_brush->SetColour(tmpCol);

	}
}

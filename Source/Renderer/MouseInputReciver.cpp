#include "MouseInputReciver.h"
#include<windowsx.h>



MouseInputReciver::MouseInputReciver()
{
}


MouseInputReciver::~MouseInputReciver()
{
}

bool MouseInputReciver::TryProcessMouseMessage(MSG msg)
{
	bool isMouseMsg = true;;
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		mMouseInfo = MouseInfo();
		mMouseInfo
		
		mPrevXPos = GET_X_LPARAM(msg.lParam);
		mPrevYPos = GET_Y_LPARAM(msg.lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		int newXPos = GET_X_LPARAM(msg.lParam);
		int newYPos = GET_Y_LPARAM(msg.lParam);

		int dXPos = newXPos - mPrevXPos;
		int dYPos = newYPos - mPrevYPos;

		mPrevXPos = newXPos;
		mPrevYPos = newYPos;
		break;
	}
	case WM_LBUTTONUP:
	{
		mPrevXPos = -1;
		mPrevYPos = -1;
		break;
	}
	case RI_MOUSE_WHEEL:
	{
		break;
	}
	default:
		isMouseMsg = false;
		break;
	}
	return isMouseMsg;
}

MouseInfo::MouseInfo(eMouseType mouseType, int currentXPos, int currentYPos, int dXPos, int dYPos)
	: MouseType(mouseType), CurrentXPos(currentXPos), CurrentYPos(currentYPos), DXPos(DXPos), DYPos(dYPos)
{

}

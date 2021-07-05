#include "MouseInputReciver.h"
#include<windowsx.h>




bool MouseInputReciver::TryProcessMouseMessage(MSG msg)
{
	bool isMouseMsg = true;;
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		mMouseInfo.MouseType = eMouseType::LButton;
		int mouseXPos = GET_X_LPARAM(msg.lParam);
		int mouseYPos = GET_Y_LPARAM(msg.lParam);
		mMouseInfo.CurrentXPos = mouseXPos;
		mMouseInfo.CurrentYPos = mouseYPos;


		break;
	}
	case WM_MOUSEMOVE:
	{
		int mouseXPos = GET_X_LPARAM(msg.lParam);
		int mouseYPos = GET_Y_LPARAM(msg.lParam);
		mMouseInfo.CurrentXPos = mouseXPos;
		mMouseInfo.CurrentYPos = mouseYPos;
		mMouseInfo.DXPos = mouseXPos - mMouseInfo.CurrentXPos;
		mMouseInfo.DYPos = mouseYPos = mMouseInfo.CurrentYPos;


		break;
	}
	case WM_LBUTTONUP:
	{
		mMouseInfo.MouseType = eMouseType::None;
		mMouseInfo.DXPos = -1;
		mMouseInfo.DYPos = -1;
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

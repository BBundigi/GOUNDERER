#include "MouseInputReciver.h"
#include<windowsx.h>




MouseInputReciver::MouseInputReciver()
	: mMouseButtonType(eMouseType::None), mMouseInfo()
{
}

bool MouseInputReciver::TryProcessMouseMessage(MSG msg)
{
	bool isMouseMsg = true;;
	switch (msg.message)
	{
		case WM_LBUTTONDOWN:
		{
			PoccessMouseInput(eMouseType::LButton, msg.lParam);
			break;
		}
		case WM_LBUTTONUP:
		{
			ClearMouseInfo();
			break;
		}
		case WM_RBUTTONDOWN:
		{
			PoccessMouseInput(eMouseType::RButton, msg.lParam);
			break;
		}
		case WM_RBUTTONUP:
		{
			ClearMouseInfo();
			break;
		}

		case WM_MOUSEMOVE:
		{
			PoccessMouseInput(mMouseInfo.MouseType, msg.lParam);
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

void MouseInputReciver::ConvertMousePos(const int mouseXPos, const int mouseYPos, int* const rendererXPos, int* const rendererYPos)
{
	*rendererXPos = mouseXPos - APP_WIDTH / 2;
	*rendererYPos = APP_HEIGHT / 2 - mouseYPos;
}

void MouseInputReciver::PoccessMouseInput(eMouseType inputMouseType, LPARAM msgParam)
{
	int mouseXPos = GET_X_LPARAM(msgParam);
	int mouseYPos = GET_Y_LPARAM(msgParam);
	int renderXPos, renderYPos;
	ConvertMousePos(mouseXPos, mouseYPos, &renderXPos, &renderYPos);

	mMouseInfo.CurrentXPos = renderXPos;
	mMouseInfo.CurrentYPos = renderYPos;
	if (mMouseInfo.MouseType != eMouseType::None)
	{
		mMouseInfo.DXPos = renderXPos - mMouseInfo.CurrentXPos;
		mMouseInfo.DYPos = renderYPos - mMouseInfo.CurrentYPos;
	}
	mMouseInfo.MouseType = inputMouseType;
}

void MouseInputReciver::ClearMouseInfo()
{
	mMouseInfo.MouseType = eMouseType::None;
	mMouseInfo.DXPos = -1;
	mMouseInfo.DYPos = -1;
}

MouseInfo::MouseInfo(eMouseType mouseType, int currentXPos, int currentYPos, int dXPos, int dYPos)
	: MouseType(mouseType), CurrentXPos(currentXPos), CurrentYPos(currentYPos), DXPos(dXPos), DYPos(dYPos)
{

}

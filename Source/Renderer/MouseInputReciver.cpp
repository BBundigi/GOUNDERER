#include "MouseInputReciver.h"



MouseInputReciver::MouseInputReciver()
{
}


MouseInputReciver::~MouseInputReciver()
{
}

void MouseInputReciver::ProcessMouseMessage(MSG msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		break;
	}
	case WM_MOUSEMOVE:
	{
		break;
	}
	case RI_MOUSE_WHEEL:
	{

	}
	default:
		break;
	}
}

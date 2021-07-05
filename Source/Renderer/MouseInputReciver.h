#pragma once
#include<Windows.h>

enum eMouseType
{
	None,
	LButton,
	MButton,
	RButton,
};
struct MouseInfo
{
	MouseInfo() = default;
	MouseInfo(eMouseType mouseType, int currentXPos, int currentYPos, int dXPos, int dYPos);
	eMouseType MouseType;
	int CurrentXPos;
	int CurrentYPos;
	int DXPos;
	int DYPos;
};

class MouseInputReciver
{
public:
	MouseInputReciver() = default;
    virtual	~MouseInputReciver() = default;
	bool TryProcessMouseMessage(MSG msg);
	inline MouseInfo GetMouseInfo()
	{
		return mMouseInfo;
	}
private:
	eMouseType mMouseButtonType;
	MouseInfo mMouseInfo;
};

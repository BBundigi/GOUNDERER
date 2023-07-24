#pragma once
#include<Windows.h>
#include<AppDefinition.h>

enum class eMouseType
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
	MouseInputReciver();
    virtual	~MouseInputReciver() = default;
	bool TryProcessMouseMessage(MSG msg);
	inline MouseInfo GetMouseInfo()
	{
		return mMouseInfo;
	}
private:
	eMouseType mMouseButtonType;
	MouseInfo mMouseInfo;
	void ConvertMousePos(const int mouseXPos, const int mouseYPos, int* const rendererXPos, int* const rendererYPos);
	void PoccessMouseInput(eMouseType inputMouseType, LPARAM msgParam);
	void ClearMouseInfo();
};

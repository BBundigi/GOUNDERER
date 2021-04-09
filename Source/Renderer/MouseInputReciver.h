#pragma once
#include<Windows.h>
class MouseInputReciver
{
public:
	MouseInputReciver();
	~MouseInputReciver();
	void ProcessMouseMessage(MSG msg);
};


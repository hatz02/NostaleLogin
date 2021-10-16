#pragma once
#include "Structures.h"
#include <Windows.h>

class GraphicButtonWidget
{
public:
	GraphicButtonWidget(TEWGraphicButtonWidget* widget) : buttonWidget(widget) {};

	void clickButton()
	{
		DWORD parametersAddress = buttonWidget->parameters;
		DWORD callAddress = buttonWidget->clickFunction;
		TEWGraphicButtonWidget* selfButton = buttonWidget;

		__asm
		{
			mov eax, parametersAddress
			mov edx, selfButton
			call callAddress
		};
	}

private:
	TEWGraphicButtonWidget* buttonWidget;
};

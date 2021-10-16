#pragma once
#include "Structures.h"
#include "GraphicButtonWidget.h"

class NewServerSelectWidget
{
public:
	NewServerSelectWidget();

	void selectLanguage(int lang);

	void selectServer(int server);

	void selectChannel(int channel);

	bool isVisible() const;

private:
	TNTNewServerSelectWidget2* getNewServerSelectWidget() const;

	DWORD address;
};


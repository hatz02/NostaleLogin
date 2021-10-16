#include "NewServerSelectWidget.h"
#include "PatternScanner.h"
#include <iostream>

NewServerSelectWidget::NewServerSelectWidget()
{
	address = PatternScan(
		"\xa1\x00\x00\x00\x00\x8b\x00\xc6\x40\x00\x00\xa1\x00\x00\x00\x00\xc7\x00",
		"x????xxxx??x????xx",
		1
	);
}

void NewServerSelectWidget::selectLanguage(int lang)
{
	if (lang < 0) return;

	TNTNewServerSelectWidget2* newServerSelectWidget = getNewServerSelectWidget();
	if (!newServerSelectWidget) return;

	GraphicButtonWidget button(newServerSelectWidget->selectLanguageButton);
	newServerSelectWidget->selectLanguageButton->selectedIndex = lang;
	button.clickButton();
}

void NewServerSelectWidget::selectServer(int server)
{
	if (server < 0) return;

	TNTNewServerSelectWidget2* newServerSelectWidget = getNewServerSelectWidget();
	if (!newServerSelectWidget) return;

	GraphicButtonWidget button(newServerSelectWidget->selectServerButton);
	newServerSelectWidget->selectServerButton->selectedIndex = server;
	button.clickButton();
}

void NewServerSelectWidget::selectChannel(int channel)
{
	if (channel < 0) return;

	TNTNewServerSelectWidget2* newServerSelectWidget = getNewServerSelectWidget();
	if (!newServerSelectWidget) return;

	GraphicButtonWidget button(newServerSelectWidget->selectChannelButton);
	newServerSelectWidget->selectChannelButton->selectedIndex = channel;
	button.clickButton();
}

bool NewServerSelectWidget::isVisible() const
{
	TNTNewServerSelectWidget2* newServerSelectWidget = getNewServerSelectWidget();
	if (!newServerSelectWidget) return false;

	return newServerSelectWidget->isVisible;
}

TNTNewServerSelectWidget2* NewServerSelectWidget::getNewServerSelectWidget() const
{
	DWORD addy = address;

	addy = READ_PTR(addy, 0);
	addy = READ_PTR(addy, 0);
	addy = READ_PTR(addy, 0);
	addy = READ_PTR(addy, 0x28);

	TNTNewServerSelectWidget2* serverSelectWidget = (TNTNewServerSelectWidget2*)addy;

	if (IsBadReadPtr(serverSelectWidget, sizeof(TNTNewServerSelectWidget2)))
		return nullptr;

	return serverSelectWidget;
}
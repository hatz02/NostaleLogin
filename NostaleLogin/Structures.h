#pragma once
#include <cstdint>

#define READ_PTR(ptr, offset) *(uintptr_t*)(ptr + offset); if (ptr == 0) return 0;

// Created with ReClass.NET 1.2 by KN4CK3R

class TLBSWidget
{
public:
	uint32_t vTable; //0x0000
	char pad_0004[20]; //0x0004
	uint8_t isVisible; //0x0018
	uint8_t isClickable; //0x0019
	char pad_001A[10]; //0x001A
}; //Size: 0x0024
static_assert(sizeof(TLBSWidget) == 0x24, "TLBSWidget does not have a size of 0x24");

class TNTNewServerSelectWidget2 : public TLBSWidget
{
public:
	char pad_0024[80]; //0x0024
	class TEWGraphicButtonWidget* selectLanguageButton; //0x0074
	char pad_0078[140]; //0x0078
	class TEWGraphicButtonWidget* selectServerButton; //0x0104
	class TEWGraphicButtonWidget* selectChannelButton; //0x0108
	char pad_010C[344]; //0x010C
}; //Size: 0x0264
static_assert(sizeof(TNTNewServerSelectWidget2) == 0x264, "TNTNewServerSelectWidget2 does not have a size of 0x264");

class TEWGraphicButtonWidget : public TLBSWidget
{
public:
	char pad_0024[60]; //0x0024
	int32_t selectedIndex; //0x0060
	char pad_0064[76]; //0x0064
	uint32_t clickFunction; //0x00B0
	uint32_t parameters; //0x00B4
	char pad_00B8[36]; //0x00B8
}; //Size: 0x00DC
static_assert(sizeof(TEWGraphicButtonWidget) == 0xDC, "TEWGraphicButtonWidget does not have a size of 0xDC");
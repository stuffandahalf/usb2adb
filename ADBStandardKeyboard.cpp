#include <Arduino.h>
#include "ADBStandardKeyboard.h"

ADBStandardKeyboard::ADBStandardKeyboard()
: ADB(2, ADB_DEFAULT_ADDRESS_KEYBOARD, false), r0(0), r2(0)
{
	
}

ADBStandardKeyboard::~ADBStandardKeyboard() { }

void ADBStandardKeyboard::setKeyState(char c, bool state)
{
	byte newValue = (state << 7) | (c & 0x7F);
	if (!(this->r0 >> 8)) {
		this->r0 = newValue << 8;
	} else if (!(this->r0 & 0xFF)) {
		this->r0 |= newValue;
	}
}

void ADBStandardKeyboard::reset()
{
	ADB::reset();
	
	this->r0 = 0;
	this->r2 = 0;
}

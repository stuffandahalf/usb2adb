#include <Arduino.h>
#include "KeyReportHandler.h"

KeyReportHandler::KeyReportHandler(volatile ADBStandardKeyboard& kb)
: KeyboardReportParser(), kb(kb)
{
	
}

void
KeyReportHandler::OnControlKeysChanged(uint8_t before, uint8_t after)
{
	MODIFIERKEYS beforeMod, afterMod;
	beforeMod = *(MODIFIERKEYS *)&before;
	afterMod = *(MODIFIERKEYS *)&after;
	
	
}

void
KeyReportHandler::OnKeyDown(uint8_t mod, uint8_t key)
{
	char c = OemToAscii(mod, key);
	Serial.println(c);
	this->kb.setKeyState(c, ADB_STD_KB_KEY_DOWN);
}

void
KeyReportHandler::OnKeyUp(uint8_t mod, uint8_t key)
{
	
}

void
KeyReportHandler::OnKeyPressed(uint8_t key)
{
	
}

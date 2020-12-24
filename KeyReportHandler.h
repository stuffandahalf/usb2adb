#ifndef ADB2USB_KEYBOARDREPORTHANDLER
#define ADB2USB_KEYBOARDREPORTHANDLER	1

#pragma once

#include <hidboot.h>

class KeyReportHandler : public KeyboardReportParser {
private:
	//void PrintKey(uint8_t mod, uint8_t key);

protected:
	virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

	virtual void OnKeyDown(uint8_t mod, uint8_t key);
	virtual void OnKeyUp(uint8_t mod, uint8_t key);
	virtual void OnKeyPressed(uint8_t key);
};

#endif /* ADB2USB_KEYBOARDREPORTHANDLER */

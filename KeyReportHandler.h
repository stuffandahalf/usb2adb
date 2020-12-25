#ifndef USB2ADB_KEYREPORTHANDLER
#define USB2ADB_KEYREPORTHANDLER	1

#pragma once

#include <hidboot.h>
#include "ADBStandardKeyboard.h"

class KeyReportHandler : public KeyboardReportParser {
private:
	volatile ADBStandardKeyboard& kb;
	//void PrintKey(uint8_t mod, uint8_t key);

public:
	KeyReportHandler(volatile ADBStandardKeyboard& kb);
	virtual ~KeyReportHandler() { }

protected:

	virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

	virtual void OnKeyDown(uint8_t mod, uint8_t key);
	virtual void OnKeyUp(uint8_t mod, uint8_t key);
	virtual void OnKeyPressed(uint8_t key);
	
	
};

#endif /* USB2ADB_KEYREPORTHANDLER */

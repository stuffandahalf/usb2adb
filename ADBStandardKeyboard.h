#ifndef USB2ADB_ADBSTANDARDKEYBOARD_H
#define USB2ADB_ADBSTANDARDKEYBOARD_H	1

#include "ADB.h"

static const bool ADB_STD_KB_KEY_DOWN = false;
static const bool ADB_STD_KB_KEY_UP = true;

class ADBStandardKeyboard : public ADB {
private:
	unsigned short r0;
	unsigned short r2;
	
public:
	ADBStandardKeyboard();
	virtual ~ADBStandardKeyboard();
	
	void setKeyState(char c, bool state);
	virtual void reset();
};

#endif /* USB2ADB_ADBSTANDARDKEYBOARD_H */

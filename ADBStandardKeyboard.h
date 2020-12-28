// SPDX-License-Identifier: GPL-3.0-only
//
// Copyright (C) 2020 Gregory Norton <gregory.norton@me.com>
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
// 
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef USB2ADB_ADBSTANDARDKEYBOARD_H
#define USB2ADB_ADBSTANDARDKEYBOARD_H	1

#include "ADBDevice.h"

static const bool ADB_STD_KB_KEY_DOWN = false;
static const bool ADB_STD_KB_KEY_UP = true;

class ADBStandardKeyboard : public ADBDevice {
private:
	uint16_t r0;
	uint16_t r2;
	
public:
	ADBStandardKeyboard();
	virtual ~ADBStandardKeyboard();
	
	void setKeyState(char c, bool state);
	virtual void reset();
	virtual bool getRegister(unsigned int index, Register& out);
};

#endif /* USB2ADB_ADBSTANDARDKEYBOARD_H */
